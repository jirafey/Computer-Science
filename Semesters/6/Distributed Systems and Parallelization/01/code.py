import re
import sys
from collections import defaultdict

def parse_results(filename="sprawozdanie_results.txt"):
    """Parses the results file and returns a structured dictionary."""
    results = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(dict))))
    # Structure: results[schedule_key][size][threads][loop] = {'time': float, 'verify': str}

    current_size = None
    current_threads = None
    current_schedule_key = None # e.g., "Static,10", "Dynamic,50", "Default (Static)"

    size_pattern = re.compile(r"--- Matrix Size: (\d+) x \d+ ---")
    threads_pattern = re.compile(r"\*\*\* Threads: (\d+) \*\*\*")
    schedule_pattern = re.compile(r"Schedule: (.*)")
    # Main data pattern to capture necessary fields
    data_pattern = re.compile(
        r"Size: (?P<size>\d+)x\d+, "
        r"Threads: (?P<threads>\d+), "
        r"Loop: (?P<loop>[123]), "
        # Schedule might have comma, handle variations
        r"Schedule: (?P<schedule_str>.*?),"
        r" Time\(Seq\): .*? ms," # Ignore sequential time here
        r" Time\(Par\): (?P<time_par>[\d.]+) ms,"
        r" Verify: (?P<verify>\w+)"
    )

    try:
        with open(filename, 'r') as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.", file=sys.stderr)
        sys.exit(1)

    for i, line in enumerate(lines):
        line = line.strip()

        # Update context based on headers
        match_size = size_pattern.search(line)
        if match_size:
            current_size = int(match_size.group(1))
            continue

        match_threads = threads_pattern.search(line)
        if match_threads:
            current_threads = int(match_threads.group(1))
            continue

        match_schedule = schedule_pattern.search(line)
        if match_schedule:
            current_schedule_key = match_schedule.group(1).strip()
            # Look ahead slightly for the data line associated with this schedule
            if i + 1 < len(lines):
                next_line = lines[i+1].strip()
                match_data = data_pattern.search(next_line)
                if match_data:
                     # Check context consistency
                    data_size = int(match_data.group('size'))
                    data_threads = int(match_data.group('threads'))

                    if data_size == current_size and data_threads == current_threads:
                        loop = int(match_data.group('loop'))
                        time_par = float(match_data.group('time_par'))
                        verify = match_data.group('verify')
                        verify_char = 'M' if verify.lower() == 'match' else 'F' # Or use first letter directly if output is M/F

                        # Store the result
                        results[current_schedule_key][current_size][current_threads][loop] = {
                            'time': time_par,
                            'verify': verify_char
                        }
                    else:
                        # This shouldn't happen if the log file is consistent
                        print(f"Warning: Context mismatch on data line after schedule '{current_schedule_key}'", file=sys.stderr)

    return results

def generate_markdown(results, sizes, threads_list, schedules):
    """Generates Markdown tables from the parsed results."""

    markdown = ""

    # --- Sequential Time Table (Requires manual input or separate parsing) ---
    # This script focuses on parallel results. Add the sequential table manually
    # or modify the parser to capture it if needed.
    markdown += "### Czas Wykonania Sekwencyjnego\n\n"
    markdown += "| Rozmiar Macierzy | Czas Sekwencyjny (ms) |\n"
    markdown += "| :--------------- | :-------------------- |\n"
    markdown += "| 100x100          | *[Wpisz czas]*        |\n"
    markdown += "| 500x500          | *[Wpisz czas]*        |\n"
    markdown += "| 1000x1000         | *[Wpisz czas]*        |\n"
    markdown += "| 2000x2000         | *[Wpisz czas]*        |\n\n"
    markdown += "*(Wypełnij powyższą tabelę czasami sekwencyjnymi ręcznie lub dostosuj parser)*\n\n"


    markdown += "### Czasy Wykonania Równoległego\n\n"
    markdown += "Wyniki przedstawiono w formacie: **Czas (ms) (Weryfikacja)**, gdzie Weryfikacja to **M** (Match - zgodne) lub **F** (Fail/MISMATCH - niezgodne).\n\n"

    for schedule_key, schedule_title in schedules.items():
        markdown += f"#### Harmonogram: **{schedule_title}**\n\n"
        # Header
        markdown += "| Rozmiar   | " + " | ".join([f"Wątki: {t}" for t in threads_list]) + " |\n"
        # Separator
        markdown += "| :-------- |" + " :--: |" * len(threads_list) + "\n" # Centered columns

        # Data Rows
        for size in sizes:
            markdown += f"| **{size}x{size}** |"
            for threads in threads_list:
                cell_content = []
                for loop in [1, 2, 3]:
                    data = results.get(schedule_key, {}).get(size, {}).get(threads, {}).get(loop)
                    if data:
                        time_str = f"{data['time']:.1f}" # Format time to 1 decimal place
                        verify_str = data['verify']
                        cell_content.append(f"L{loop}: {time_str} ({verify_str})")
                    else:
                        cell_content.append(f"L{loop}: - (X)") # Placeholder for missing data

                markdown += f" {'<br>'.join(cell_content)} |" # Use <br> for line breaks within cell
            markdown += "\n"
        markdown += "\n" # Add space after table

    return markdown

# --- Main Execution ---
if __name__ == "__main__":
    SIZES_TO_PROCESS = [100, 500, 1000, 2000]
    THREADS_TO_PROCESS = [2, 4, 8, 16]
    # Map schedule keys found in the file to desired table titles
    SCHEDULES_TO_PROCESS = {
        "Default (Static)": "Domyślny (Static)",
        "static,10": "Static, chunk 10",
        "static,50": "Static, chunk 50",
        "static,100": "Static, chunk 100",
        "dynamic,10": "Dynamic, chunk 10",
        "dynamic,50": "Dynamic, chunk 50",
        "dynamic,100": "Dynamic, chunk 100",
        "guided,10": "Guided, chunk 10",
        "guided,50": "Guided, chunk 50",
        "guided,100": "Guided, chunk 100",
    }

    # 1. Parse the results file
    parsed_data = parse_results("sprawozdanie_results.txt")

    # 2. Generate the Markdown content
    markdown_output = generate_markdown(parsed_data, SIZES_TO_PROCESS, THREADS_TO_PROCESS, SCHEDULES_TO_PROCESS)

    # 3. Write to a Markdown file
    output_filename = "sprawozdanie_generated.md"
    try:
        with open(output_filename, 'w') as f:
            f.write(markdown_output)
        print(f"Markdown tables successfully generated in '{output_filename}'")
        print("Please add the 'Wprowadzenie', 'Specyfikacja Systemu', 'Wnioski', and sequential times manually.")
    except IOError as e:
        print(f"Error writing Markdown file '{output_filename}': {e}", file=sys.stderr)