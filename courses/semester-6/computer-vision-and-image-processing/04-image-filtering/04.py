import numpy as np
import matplotlib.pyplot as plt
import cv2
# Palettes
palette1bit = np.array([[0.0], [1.0]])  # 1-bit (2 colors)
palette2bit = np.linspace(0, 1, 4).reshape(4, 1)  # 2-bit (4 colors)
palette4bit = np.linspace(0, 1, 16).reshape(16, 1)  # 4-bit (16 colors)

palette8 = np.array([
    [0.0, 0.0, 0.0, ],
    [0.0, 0.0, 1.0, ],
    [0.0, 1.0, 0.0, ],
    [0.0, 1.0, 1.0, ],
    [1.0, 0.0, 0.0, ],
    [1.0, 0.0, 1.0, ],
    [1.0, 1.0, 0.0, ],
    [1.0, 1.0, 1.0, ],
])

palette16 = np.array([
    [0.0, 0.0, 0.0, ],
    [0.0, 1.0, 1.0, ],
    [0.0, 0.0, 1.0, ],
    [1.0, 0.0, 1.0, ],
    [0.0, 0.5, 0.0, ],
    [0.5, 0.5, 0.5, ],
    [0.0, 1.0, 0.0, ],
    [0.5, 0.0, 0.0, ],
    [0.0, 0.0, 0.5, ],
    [0.5, 0.5, 0.0, ],
    [0.5, 0.0, 0.5, ],
    [1.0, 0.0, 0.0, ],
    [0.75, 0.75, 0.75, ],
    [0.0, 0.5, 0.5, ],
    [1.0, 1.0, 1.0, ],
    [1.0, 1.0, 0.0, ]
])

def image_vars(image, scale):
    original_height, original_width, channels = image.shape
    new_width = int(original_width * scale)
    new_height = int(original_height * scale)
    resized_image = np.zeros((new_height, new_width, channels), dtype=np.uint8)
    return original_height, original_width, channels, new_width, new_height, resized_image

def colorFit(pixel, Palette):
    distance_between_colors = np.linalg.norm(Palette - pixel, axis = 1) # euclidian
    minimum = np.argmin(distance_between_colors)
    # smallest distance between the colors in a palette
    return Palette[minimum] # return the closest color

def kwant_colorFit(img, Palette):
    height, width, channels = img.shape
    out_img = img.copy()
    for w in range(height):
        for k in range(width):
            out_img[w,k]=colorFit(img[w,k],Palette)
    return out_img

# def main():
    # paleta = np.linspace(0, 1, 3).reshape(3, 1)
    # print(paleta)

    # print(colorFit(0.43, paleta))  # 0.5
    # print(colorFit(0.66, paleta))  # 0.5
    # print(colorFit(0.8, paleta))  # 1.

    # print(colorFit(np.array([0.25, 0.25, 0.5]), pallet8)) # [0,0,0]
    # print(colorFit(np.array([0.25, 0.25, 0.5]), pallet16)) # [0.5,0.5,0.5]

    # #Small images (4)
    # small_files = ['SMALL_0004.jpg', 'SMALL_0007.jpg', 'SMALL_0009.jpg', 'SMALL_0001.tif'][:4]
    # for file in small_files:
    #     img = cv2.imread('IMG_SMALL/' + file)
    #     if img is None:
    #         print(f"Błąd: nie udało się wczytać {file}")
    #     img = kwant_colorFit(img, palette16)
    #     plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    #     plt.title(f"{file}\n")
    #     plt.tight_layout()
    #     plt.show()

    # # Big images (2)
    # big_files = ['BIG_0001.jpg', 'BIG_0004.png'][:2]
    #
    # for file in big_files:
    #     img = cv2.imread('IMG_BIG/' + file)
    #     img = kwant_colorFit(img, palette16)
    #     plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    #     plt.title(f"{file}\n")
    #     plt.tight_layout()
    #     plt.show()


# dithering

def random_dithering(img, palette):
    height, width, channels = img.shape
    out_img = img.copy()
    r=np.random.rand(height,width)
    dithered = (img >= r).astype(float) # if img>= -> 1.0 else: 0.0

    return kwant_colorFit(dithered, palette)

def organized_dithering(img, palette, r=1):
    height, width, channels = img.shape
    M1 = np.array([[0, 2], [3, 1]])
    M2 = np.array([[0, 8, 2, 10], [12, 4, 14, 6], [3,11,1,9], [15,7,13,5]])
    M4 = np.array([
        [0, 32, 8, 40, 2, 34, 10, 42],
        [48, 16, 56, 24, 50, 18, 58, 26],
        [12, 44, 4, 36, 14, 46, 6, 38],
        [60, 28, 52, 20, 62, 30, 54, 22],
        [3, 35, 11, 43, 1, 33, 9, 41],
        [51, 19, 59, 27, 49, 17, 57, 25],
        [15, 47, 7, 39, 13, 45, 5, 37],
        [63, 31, 55, 23, 61, 29, 53, 21]
    ])
    M = M2
    n = 2
    Mpre = (M + 1) / (2 * n) ** 2 - 0.5
    out_img = np.zeros_like(img)
    _2n = 2*n
    for i in range(height):
        for j in range(width):
            index_i= i % _2n
            index_j= j % _2n
            m_val= Mpre[index_i, index_j]
            temp_val = img[i, j] + m_val * r
            out_img[i,j] = colorFit(temp_val, palette)
    return out_img


def floyd_steinberg(img, palette):
    img = img.copy().astype(float)
    height, width = img.shape[:2]

    for x in range(height):
        for y in range(width):
            old_pixel = img[x, y]
            new_pixel = colorFit(old_pixel, palette)
            img[x, y] = new_pixel
            quant_error = old_pixel - new_pixel

            if y + 1 < width:  # Right
                img[x, y + 1] += quant_error * 7 / 16
            if x + 1 < height:
                if y - 1 >= 0:  # Bottom-left
                    img[x + 1, y - 1] += quant_error * 3 / 16
                img[x + 1, y] += quant_error * 5 / 16  # Bottom
                if y + 1 < width:  # Bottom-right
                    img[x + 1, y + 1] += quant_error * 1 / 16
    return img


def process_and_plot(image_path):
    # Load and normalize image
    img = cv2.imread(image_path)
    if img is None:
        print(f"Error loading {image_path}")
        return

    # Convert to float [0,1]
    img_float = img.astype(float) / 255.0

    # Create figure for bit-depth comparison
    fig1, axs1 = plt.subplots(3, 4, figsize=(20, 15))
    fig1.suptitle(f"Bit Depth Comparison - {image_path}", fontsize=16)

    # Process for 1-bit, 2-bit, 4-bit
    for i, (bit_depth, palette) in enumerate(zip(
            ['1-bit', '2-bit', '4-bit'],
            [palette1bit, palette2bit, palette4bit]
    )):
        # Original
        axs1[i, 0].imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        axs1[i, 0].set_title(f"{bit_depth}\nOriginal")
        axs1[i, 0].axis('off')

        # Quantization
        quant = kwant_colorFit(img_float, palette)
        axs1[i, 1].imshow(quant)
        axs1[i, 1].set_title("Quantization")
        axs1[i, 1].axis('off')

        # Organized Dithering
        org = organized_dithering(img_float, palette)
        axs1[i, 2].imshow(org)
        axs1[i, 2].set_title("Organized Dithering")
        axs1[i, 2].axis('off')

        # Floyd-Steinberg
        fs = floyd_steinberg(img_float, palette)
        axs1[i, 3].imshow(fs)
        axs1[i, 3].set_title("Floyd-Steinberg")
        axs1[i, 3].axis('off')

    plt.tight_layout()

    # Create figure for palette comparison (8 vs 16 colors)
    fig2, axs2 = plt.subplots(2, 4, figsize=(20, 10))
    fig2.suptitle(f"Palette Comparison - {image_path}", fontsize=16)

    # Process for 8 and 16 color palettes
    for i, (palette, name) in enumerate(zip(
            [palette8, palette16],
            ['8-color', '16-color']
    )):
        # Original
        axs2[i, 0].imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
        axs2[i, 0].set_title(f"{name}\nOriginal")
        axs2[i, 0].axis('off')

        # Quantization
        quant = kwant_colorFit(img_float, palette)
        axs2[i, 1].imshow(quant)
        axs2[i, 1].set_title("Quantization")
        axs2[i, 1].axis('off')

        # Organized Dithering
        org = organized_dithering(img_float, palette)
        axs2[i, 2].imshow(org)
        axs2[i, 2].set_title("Organized Dithering")
        axs2[i, 2].axis('off')

        # Floyd-Steinberg
        fs = floyd_steinberg(img_float, palette)
        axs2[i, 3].imshow(fs)
        axs2[i, 3].set_title("Floyd-Steinberg")
        axs2[i, 3].axis('off')

    plt.tight_layout()
    plt.show()


# # Process sample images
# image_files = ['GS_0001.tif', 'GS_0002.png', 'GS_0003.png']
# for file in image_files:
#     process_and_plot(f'IMG_GS/{file}')
#
# Process sample images
image_files = ['SMALL_0004.jpg', 'SMALL_0006.jpg', 'SMALL_0009.jpg']
for file in image_files:
    process_and_plot(f'IMG_SMALL/{file}')