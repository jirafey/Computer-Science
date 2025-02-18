
import pygame
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
import os

# --- Default Parameters & Test Cases ---
PARAMS_INIT = {
    "g": 9.81, "m1": 0.5, "m2": 0.9, "M_pulley": 1.0, "R_pulley": 0.001,
    "r0": 1.0, "theta0_deg": 120.0, "rdot0": 0.0, "thetadot0": 0.0
}
L_SYSTEM_TOTAL_INIT = PARAMS_INIT["r0"] * 2.0

TEST_CASES = {
    "Test Case 1": PARAMS_INIT,
    "Test Case 2": {"g": 9.81, "m1": 1.0, "m2": 2.0, "M_pulley": 1.0, "R_pulley": 0.002,
                    "r0": 0.5, "theta0_deg": 90.0, "rdot0": 0.0, "thetadot0": 0.0},
    "Test Case 3": {"g": 9.81, "m1": 2.2, "m2": 2.0, "M_pulley": 3.0, "R_pulley": 0.002,
                    "r0": 2.0, "theta0_deg": 45.0, "rdot0": 0.0, "thetadot0": 0.0}
}
for tc_name, tc_params in TEST_CASES.items():
    if "L_sys" not in tc_params: tc_params["L_sys"] = tc_params["r0"] * 2.0

# --- Simulation Constants ---
T_SIM_MAX = 50.0
ODE_MAX_STEP = 2 ** -5
R_MIN_COLLISION = 1e-4

# --- Visualization ---
LOGICAL_WIDTH = 1000;
LOGICAL_HEIGHT = 750;
INITIAL_SCREEN_WIDTH = 1000;
INITIAL_SCREEN_HEIGHT = 750
FPS = 60;
PIXELS_PER_METER_LOGICAL = 70;
PULLEY_Y_LOGICAL = 150;
MASS_WIDTH_LOGICAL = 20
D_PULLEYS_HORIZONTAL = 1.5

BLACK, WHITE, RED, BLUE, GREY, GREEN, ORANGE, PURPLE, LIGHT_BLUE = \
    (0, 0, 0), (255, 255, 255), (200, 50, 50), (50, 50, 200), (150, 150, 150), \
        (50, 200, 50), (255, 165, 0), (128, 0, 128), (173, 216, 230)

sim_params = PARAMS_INIT.copy();
l_system_total_current = L_SYSTEM_TOTAL_INIT
current_display_state = {"r": None, "theta": None, "rdot": None, "thetadot": None}
t_current_display = 0.0;
solution = None
plot_data_custom = {"time": [], "x_m1": [], "y_m1": []}


# --- ODE System Definition ---
def swinging_atwood_odes_lab6(t, y_vec, g, m1, m2, M_p, R_p):
    r, theta, r_dot, theta_dot = y_vec
    if abs(r) < R_MIN_COLLISION / 10: return [r_dot, theta_dot, 1e7, 1e7]
    K = m1 + m2 + M_p / 2.0;
    A11 = K;
    A12 = -K * R_p
    B1 = m1 * r * theta_dot ** 2 + g * (m1 * np.cos(theta) - m2)
    A21 = -K * R_p;
    A22 = K * R_p ** 2 + m1 * r ** 2
    B2 = g * R_p * (m2 - m1 * np.cos(theta)) - m1 * r * (2 * r_dot * theta_dot + g * np.sin(theta))
    det_A = A11 * A22 - A12 * A21
    if abs(det_A) < 1e-12:
        return [r_dot, theta_dot,
                np.sign(B1 * A22 - B2 * A12) * 1e7 if (B1 * A22 - B2 * A12) != 0 else 0,
                np.sign(A11 * B2 - A21 * B1) * 1e7 if (A11 * B2 - A21 * B1) != 0 else 0]
    return [r_dot, theta_dot, (B1 * A22 - B2 * A12) / det_A, (A11 * B2 - A21 * B1) / det_A]


# --- Event Functions ---
def event_r_min_pivot(t, y, g, m1, m2, M_p, R_p): return y[0] - R_MIN_COLLISION


event_r_min_pivot.terminal = True;
event_r_min_pivot.direction = -1


def event_r_max_m2_hits_pulley(t, y, g, m1, m2, M_p, R_p): return y[0] - (
            2 * sim_params.get("r0", PARAMS_INIT["r0"]) - R_MIN_COLLISION)


event_r_max_m2_hits_pulley.terminal = True;
event_r_max_m2_hits_pulley.direction = 1

# --- Pygame and GUI Setup ---
pygame.init();
screen = pygame.display.set_mode((INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT), pygame.RESIZABLE)
logical_screen = pygame.Surface((LOGICAL_WIDTH, LOGICAL_HEIGHT));
pygame.display.set_caption("Swinging Atwood (Lab 6 - Plots Saved on Quit)")
clock = pygame.time.Clock();
font_small = pygame.font.SysFont(None, 20);
font_medium = pygame.font.SysFont(None, 24)

INPUT_BOX_START_X = LOGICAL_WIDTH - 320;
INPUT_BOX_START_Y = 40
INPUT_BOX_WIDTH = 70;
INPUT_BOX_HEIGHT = 26;
INPUT_BOX_SPACING_Y = 32
input_boxes_config_swinging = [
    ("g", "g(m/s^2):", PARAMS_INIT["g"]), ("m1", "m1(kg):", PARAMS_INIT["m1"]), ("m2", "m2(kg):", PARAMS_INIT["m2"]),
    ("M_pulley", "M(bloczki):", PARAMS_INIT["M_pulley"]), ("R_pulley", "R(promień bl.):", PARAMS_INIT["R_pulley"]),
    ("r0", "r(0)(m):", PARAMS_INIT["r0"]), ("theta0_deg", "θ(0)(deg):", PARAMS_INIT["theta0_deg"]),
    ("rdot0", "r_dot(0):", PARAMS_INIT["rdot0"]), ("thetadot0", "θ_dot(0):", PARAMS_INIT["thetadot0"]),
    ("L_sys", "L_sys(m):", L_SYSTEM_TOTAL_INIT)
]
input_boxes = {}
for i, (key, label, init_val) in enumerate(input_boxes_config_swinging):
    input_boxes[key] = {
        "rect": pygame.Rect(INPUT_BOX_START_X + 130, INPUT_BOX_START_Y + i * INPUT_BOX_SPACING_Y, INPUT_BOX_WIDTH,
                            INPUT_BOX_HEIGHT),
        "text": str(init_val), "active": False, "label": label}
BUTTON_WIDTH = 130;
BUTTON_HEIGHT = 30
MAIN_BUTTON_START_Y = INPUT_BOX_START_Y + len(input_boxes_config_swinging) * INPUT_BOX_SPACING_Y + 10
reset_button_s = {"rect": pygame.Rect(INPUT_BOX_START_X, MAIN_BUTTON_START_Y, BUTTON_WIDTH, BUTTON_HEIGHT),
                  "text": "Reset & Run", "color": GREEN}
pause_button_s = {
    "rect": pygame.Rect(INPUT_BOX_START_X + BUTTON_WIDTH + 10, MAIN_BUTTON_START_Y, BUTTON_WIDTH, BUTTON_HEIGHT),
    "text": "Pause", "color": ORANGE}
TEST_CASE_BUTTON_START_Y = MAIN_BUTTON_START_Y + BUTTON_HEIGHT + 15
TEST_CASE_BUTTON_WIDTH = (BUTTON_WIDTH * 2 + 10) // 3 - 5
test_case_buttons = []
for i, tc_name in enumerate(TEST_CASES.keys()):
    test_case_buttons.append({"rect": pygame.Rect(INPUT_BOX_START_X + i * (TEST_CASE_BUTTON_WIDTH + 5),
                                                  TEST_CASE_BUTTON_START_Y, TEST_CASE_BUTTON_WIDTH, BUTTON_HEIGHT - 5),
                              "text": tc_name.replace("Test Case", "TC"), "params_name": tc_name, "color": LIGHT_BLUE})

simulation_active_s = True


def update_button_text_swinging(): global simulation_active_s; pause_button_s[
    "text"] = "Resume" if not simulation_active_s else "Pause"


def load_test_case_params(tc_name):
    params_to_load = TEST_CASES.get(tc_name);
    if not params_to_load: print(f"Error: Test case {tc_name} not found."); return
    print(f"Loading parameters for {tc_name}...")
    for key_param, value_param in params_to_load.items():
        if key_param in input_boxes: input_boxes[key_param]["text"] = str(value_param)


def reset_simulation_swinging():
    global sim_params, l_system_total_current, solution, plot_data_custom, current_display_state, t_current_display, simulation_active_s
    temp_params = {};
    try:
        for k_cfg, _, _ in input_boxes_config_swinging: temp_params[k_cfg] = float(input_boxes[k_cfg]["text"])
        if temp_params["r0"] <= R_MIN_COLLISION: raise ValueError(f"r0 must be > {R_MIN_COLLISION:.1e}")
        if temp_params["L_sys"] < temp_params["r0"] + R_MIN_COLLISION: raise ValueError(
            f"L_sys ({temp_params['L_sys']}) must be > r0 ({temp_params['r0']})")
        sim_params.update(temp_params);
        l_system_total_current = sim_params["L_sys"]
    except ValueError as e:
        print(f"Invalid input: {e}. Reverting to stored/initial parameters.")
        for k_cfg, _, _ in input_boxes_config_swinging:
            input_boxes[k_cfg]["text"] = str(
                sim_params.get(k_cfg, PARAMS_INIT.get(k_cfg) if k_cfg != "L_sys" else L_SYSTEM_TOTAL_INIT))
        l_system_total_current = sim_params.get("L_sys", L_SYSTEM_TOTAL_INIT)

    y0_vec = [sim_params["r0"], np.deg2rad(sim_params["theta0_deg"]), sim_params["rdot0"], sim_params["thetadot0"]]
    ode_args = (sim_params["g"], sim_params["m1"], sim_params["m2"], sim_params["M_pulley"], sim_params["R_pulley"])
    events = [event_r_min_pivot, event_r_max_m2_hits_pulley]
    print(
        f"Solver: r0={sim_params['r0']:.2f}, θ0={sim_params['theta0_deg']:.1f}°, T_max={T_SIM_MAX}, max_step={ODE_MAX_STEP}")
    solution = solve_ivp(swinging_atwood_odes_lab6, [0, T_SIM_MAX], y0_vec, args=ode_args, method='RK45',
                         dense_output=True, max_step=ODE_MAX_STEP, events=events)
    print(f"Solver finished: {solution.message}")
    if solution.status == -1:
        print("Integration step failed.")
    elif solution.status == 1:
        print("A termination event occurred.")
    for k in plot_data_custom: plot_data_custom[k] = []
    if solution and solution.success and len(solution.t) > 1:
        plot_data_custom["time"] = solution.t
        for i in range(len(solution.t)):
            r_i, th_i, _, _ = solution.y[:, i]
            plot_data_custom["x_m1"].append(r_i * np.sin(th_i));
            plot_data_custom["y_m1"].append(r_i * np.cos(th_i))
    t_current_display = 0.0
    if solution and solution.success and len(solution.t) > 0:
        s = solution.sol(0); current_display_state = {"r": s[0], "theta": s[1], "rdot": s[2], "thetadot": s[3]}
    else:
        current_display_state = {"r": sim_params["r0"], "theta": np.deg2rad(sim_params["theta0_deg"]),
                                 "rdot": sim_params["rdot0"], "thetadot": sim_params["thetadot0"]}
    simulation_active_s = True;
    update_button_text_swinging()


# --- Drawing Functions ---
def draw_swinging_atwood_visual(surface, r_val, theta_val, l_sys_val):
    if r_val is None or theta_val is None or l_sys_val is None: return
    drawing_width_atwood = LOGICAL_WIDTH - 350
    center_of_setup_x = drawing_width_atwood / 2
    half_D_pulleys_pixels = (D_PULLEYS_HORIZONTAL / 2) * PIXELS_PER_METER_LOGICAL
    main_pulley_LEFT_x = center_of_setup_x - half_D_pulleys_pixels
    main_pulley_RIGHT_x = center_of_setup_x + half_D_pulleys_pixels
    main_pulleys_y = PULLEY_Y_LOGICAL
    pivot_m2_x = main_pulley_LEFT_x;
    pivot_m2_y = main_pulleys_y
    len_m2_draw = max(0, l_sys_val - r_val)
    x_m2_s = pivot_m2_x;
    y_m2_s = pivot_m2_y + len_m2_draw * PIXELS_PER_METER_LOGICAL
    pygame.draw.line(surface, BLACK, (pivot_m2_x, pivot_m2_y), (x_m2_s, y_m2_s), 2);
    pygame.draw.circle(surface, BLUE, (int(x_m2_s), int(y_m2_s)), MASS_WIDTH_LOGICAL // 2)
    pygame.draw.circle(surface, GREY, (int(pivot_m2_x), int(pivot_m2_y)), MASS_WIDTH_LOGICAL // 2 + 5);
    pygame.draw.circle(surface, BLACK, (int(pivot_m2_x), int(pivot_m2_y)), MASS_WIDTH_LOGICAL // 2 + 5, 2)
    pivot_m1_x = main_pulley_RIGHT_x;
    pivot_m1_y = main_pulleys_y
    x_m1_s = pivot_m1_x + r_val * np.sin(theta_val) * PIXELS_PER_METER_LOGICAL;
    y_m1_s = pivot_m1_y + r_val * np.cos(theta_val) * PIXELS_PER_METER_LOGICAL
    pygame.draw.line(surface, BLACK, (pivot_m1_x, pivot_m1_y), (x_m1_s, y_m1_s), 2);
    pygame.draw.circle(surface, RED, (int(x_m1_s), int(y_m1_s)), MASS_WIDTH_LOGICAL // 2)
    pygame.draw.circle(surface, GREY, (int(pivot_m1_x), int(pivot_m1_y)), MASS_WIDTH_LOGICAL // 2 + 5);
    pygame.draw.circle(surface, BLACK, (int(pivot_m1_x), int(pivot_m1_y)), MASS_WIDTH_LOGICAL // 2 + 5, 2)
    y_top_string = main_pulleys_y - (MASS_WIDTH_LOGICAL // 2 + 5)
    pygame.draw.line(surface, (80, 80, 80), (pivot_m2_x, y_top_string), (pivot_m1_x, y_top_string), 2)
    pygame.draw.line(surface, GREY, (0, LOGICAL_HEIGHT - 30), (drawing_width_atwood, LOGICAL_HEIGHT - 30), 3)


def draw_gui_swinging(surface):
    for key, box_data in input_boxes.items():
        label_s = font_small.render(box_data["label"], True, BLACK);
        surface.blit(label_s,
                     (INPUT_BOX_START_X, box_data["rect"].y + (box_data["rect"].height - label_s.get_height()) // 2))
        pygame.draw.rect(surface, GREEN if box_data["active"] else GREY, box_data["rect"], 2);
        text_s = font_small.render(box_data["text"], True, BLACK)
        surface.blit(text_s, (box_data["rect"].x + 5,
                              box_data["rect"].y + (box_data["rect"].height - text_s.get_height()) // 2))
    for btn_data in [reset_button_s, pause_button_s]:
        pygame.draw.rect(surface, btn_data["color"], btn_data["rect"]);
        text_s = font_medium.render(btn_data["text"], True, BLACK)
        surface.blit(text_s, (btn_data["rect"].centerx - text_s.get_width() // 2,
                              btn_data["rect"].centery - text_s.get_height() // 2))
    for tc_btn_data in test_case_buttons:
        pygame.draw.rect(surface, tc_btn_data["color"], tc_btn_data["rect"]);
        tc_text_s = font_small.render(tc_btn_data["text"], True, BLACK)
        surface.blit(tc_text_s, (tc_btn_data["rect"].centerx - tc_text_s.get_width() // 2,
                                 tc_btn_data["rect"].centery - tc_text_s.get_height() // 2))
    info_y = TEST_CASE_BUTTON_START_Y + BUTTON_HEIGHT
    r_d, th_d, rd_d, thd_d = (current_display_state.get(k, 0) for k in ["r", "theta", "rdot", "thetadot"])
    th_d_deg = np.rad2deg(th_d if th_d is not None else 0)
    info_texts = [f"Time: {t_current_display:.2f} s", f"r: {r_d if r_d is not None else 'N/A':.3f} m",
                  f"θ: {th_d_deg:.2f}°",
                  f"r_dot: {rd_d if rd_d is not None else 'N/A':.3f} m/s",
                  f"θ_dot: {thd_d if thd_d is not None else 'N/A':.3f} rad/s"]
    cur_y_info = info_y
    for text in info_texts:
        s = font_small.render(text, True, BLACK);
        surface.blit(s, (INPUT_BOX_START_X, cur_y_info));
        cur_y_info += font_small.get_height() + 2


# --- Plotting Function ---
def generate_plots_swinging(sol, custom_data, p_sim, save_dir="images_sprawozdanie"):
    if sol is None or not hasattr(sol, 'success') or not sol.success or not hasattr(sol, 't') or len(sol.t) < 2: print(
        "No valid data."); return
    if not os.path.exists(save_dir): os.makedirs(save_dir); print(f"Created directory: {save_dir}")

    current_r0_str = f"{p_sim.get('r0', 'unk'):.1f}".replace('.', '_')
    current_theta0_str = f"{p_sim.get('theta0_deg', 'unk'):.0f}".replace('.', '_')
    base_filename = f"swinging_atwood_r0_{current_r0_str}_theta0_{current_theta0_str}_"

    fig1, axs1 = plt.subplots(2, 1, figsize=(10, 8))
    fig1.suptitle(
        f"Dynamika Wahadła: $m_1={p_sim['m1']:.2f}, m_2={p_sim['m2']:.2f}, M_p={p_sim['M_pulley']:.2f}, R_p={p_sim['R_pulley']:.3f}$\n" \
        f"$r_0={p_sim['r0']:.2f}, \\theta_0={p_sim['theta0_deg']:.1f}^\\circ$",
        fontsize=12)  # Using raw string for LaTeX
    axs1[0].plot(sol.t, sol.y[0], label=r'$r(t)$');
    axs1[0].set_title(r'Długość linki $m_1$ ($r$)');
    axs1[0].set_xlabel('Czas (s)');
    axs1[0].set_ylabel(r'$r$ (m)');
    axs1[0].grid(True);
    axs1[0].legend()
    axs1[1].plot(sol.t, np.rad2deg(sol.y[1]), label=r'$\theta(t)$');
    axs1[1].set_title(r'Kąt wahadła $m_1$ ($\theta$)');
    axs1[1].set_xlabel('Czas (s)');
    axs1[1].set_ylabel(r'$\theta$ (stopnie)');
    axs1[1].grid(True);
    axs1[1].legend()
    plt.tight_layout(rect=[0, 0, 1, 0.95]);
    plot1_fn = os.path.join(save_dir, f"{base_filename}r_theta_vs_t.png");
    plt.savefig(plot1_fn);
    print(f"Saved: {plot1_fn}");
    plt.close(fig1)

    fig2, ax2 = plt.subplots(figsize=(7, 7))
    if custom_data.get("x_m1") and custom_data.get("y_m1") and len(custom_data["x_m1"]) == len(sol.t):
        ax2.plot(custom_data["x_m1"], custom_data["y_m1"], label=r'Trajektoria $m_1$');
        ax2.plot(custom_data["x_m1"][0], custom_data["y_m1"][0], 'go', label='Start');
        ax2.plot(custom_data["x_m1"][-1], custom_data["y_m1"][-1], 'rx', label='Koniec')
        ax2.set_title(
            f'Trajektoria $m_1$ (XY) dla $r_0={p_sim["r0"]:.1f}, \\theta_0={p_sim["theta0_deg"]:.0f}^\\circ$');
        ax2.set_xlabel('x (m)');
        ax2.set_ylabel('y (m)');
        ax2.axis('equal');
        ax2.grid(True);
        ax2.legend(fontsize='small')
    else:
        ax2.set_title("Trajektoria $m_1$ (Brak/Niezgodne Dane)"); ax2.grid(True)
    plot2_fn = os.path.join(save_dir, f"{base_filename}xy_trajectory.png");
    plt.savefig(plot2_fn);
    print(f"Saved: {plot2_fn}");
    plt.close(fig2)

    fig3, axs3 = plt.subplots(2, 1, figsize=(10, 8))
    fig3.suptitle(f"Prędkości Wahadła: $r_0={p_sim['r0']:.2f}, \\theta_0={p_sim['theta0_deg']:.1f}^\\circ$",
                  fontsize=12)  # Using raw string
    axs3[0].plot(sol.t, sol.y[2], color='purple', label=r'$\dot{r}(t)$');
    axs3[0].set_title(r'Prędkość radialna ($\dot{r}$)');
    axs3[0].set_xlabel('Czas (s)');
    axs3[0].set_ylabel(r'$\dot{r}$ (m/s)');
    axs3[0].grid(True);
    axs3[0].legend()
    axs3[1].plot(sol.t, sol.y[3], color='orange', label=r'$\dot{\theta}(t)$');
    axs3[1].set_title(r'Prędkość kątowa ($\dot{\theta}$)');
    axs3[1].set_xlabel('Czas (s)');
    axs3[1].set_ylabel(r'$\dot{\theta}$ (rad/s)');
    axs3[1].grid(True);
    axs3[1].legend()  # Corrected axs3[1] here
    plt.tight_layout(rect=[0, 0, 1, 0.95]);
    plot3_fn = os.path.join(save_dir, f"{base_filename}velocities_vs_t.png");
    plt.savefig(plot3_fn);
    print(f"Saved: {plot3_fn}");
    plt.close(fig3)


# --- Main Loop ---
reset_simulation_swinging()
current_screen_width, current_screen_height = INITIAL_SCREEN_WIDTH, INITIAL_SCREEN_HEIGHT
while True:
    event_list = pygame.event.get()
    for event in event_list:
        if event.type == pygame.QUIT: pygame.quit(); generate_plots_swinging(solution, plot_data_custom,
                                                                             sim_params); exit()
        if event.type == pygame.VIDEORESIZE:
            current_screen_width, current_screen_height = event.w, event.h;
            screen = pygame.display.set_mode((current_screen_width, current_screen_height), pygame.RESIZABLE)
        scaled_mouse_pos = None
        if event.type in [pygame.MOUSEBUTTONDOWN, pygame.MOUSEMOTION]:
            mx, my = event.pos;
            if current_screen_width > 0 and current_screen_height > 0: scaled_mouse_pos = (
                mx * LOGICAL_WIDTH / current_screen_width, my * LOGICAL_HEIGHT / current_screen_height)
        if event.type == pygame.MOUSEBUTTONDOWN and scaled_mouse_pos:
            clicked_on_input = False
            for key, box_data in input_boxes.items():
                if box_data["rect"].collidepoint(scaled_mouse_pos):
                    box_data["active"] = not box_data["active"]; clicked_on_input = True
                else:
                    box_data["active"] = False
            if not clicked_on_input:
                if reset_button_s["rect"].collidepoint(scaled_mouse_pos):
                    reset_simulation_swinging()
                elif pause_button_s["rect"].collidepoint(scaled_mouse_pos):
                    simulation_active_s = not simulation_active_s; update_button_text_swinging()
                else:
                    for tc_btn in test_case_buttons:
                        if tc_btn["rect"].collidepoint(scaled_mouse_pos): load_test_case_params(
                            tc_btn["params_name"]); break
        if event.type == pygame.KEYDOWN:
            active_box_key = next((k for k, b in input_boxes.items() if b["active"]), None)
            if active_box_key:
                box = input_boxes[active_box_key]
                if event.key in [pygame.K_RETURN, pygame.K_KP_ENTER]:
                    box["active"] = False
                elif event.key == pygame.K_BACKSPACE:
                    box["text"] = box["text"][:-1]
                else:
                    char = event.unicode
                    if char.isdigit() or (char == '.' and '.' not in box["text"]) or \
                            (char == '-' and not box["text"]) or \
                            (char.lower() == 'e' and 'e' not in box["text"].lower() and box["text"] and (
                                    box["text"][-1].isdigit() or box["text"][-1] == '.')):
                        if len(box["text"]) < 10: box["text"] += char
            elif event.key == pygame.K_SPACE:
                simulation_active_s = not simulation_active_s; update_button_text_swinging()

    if simulation_active_s and solution and hasattr(solution, 'success') and solution.success and hasattr(solution,
                                                                                                          't') and len(
            solution.t) > 1:
        t_current_display += 1 / FPS
        if t_current_display > solution.t[-1]: t_current_display = solution.t[-1]
        if t_current_display < solution.t[0]: t_current_display = solution.t[0]
        try:
            y_interp = solution.sol(t_current_display)
            current_display_state = {"r": y_interp[0], "theta": y_interp[1], "rdot": y_interp[2],
                                     "thetadot": y_interp[3]}
        except ValueError as e:
            print(f"Interpolation Warning: {e}. Using last/first valid state.")
            if t_current_display <= solution.t[0]:
                y_interp = solution.y[:, 0]
            else:
                y_interp = solution.y[:, -1]
            current_display_state = {"r": y_interp[0], "theta": y_interp[1], "rdot": y_interp[2],
                                     "thetadot": y_interp[3]}

    logical_screen.fill(WHITE)
    if solution and current_display_state.get("r") is not None:
        draw_swinging_atwood_visual(logical_screen, current_display_state["r"], current_display_state["theta"],
                                    l_system_total_current)
    draw_gui_swinging(logical_screen)
    if current_screen_width > 0 and current_screen_height > 0:
        screen.blit(pygame.transform.scale(logical_screen, (current_screen_width, current_screen_height)), (0, 0))
    pygame.display.flip();
    clock.tick(FPS)