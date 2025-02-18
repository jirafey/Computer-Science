import numpy as np
import matplotlib.pyplot as plt

import cv2

directory = 'IMG_INTRO/IMG_INTRO/'
filenames = ['A1.png', 'A2.jpg', 'A3.png', 'A4.jpg', 'B01.png', 'B02.jpg']

for file in filenames:
    print(file)
    # img = plt.imread(directory + file)
    img = cv2.imread(directory + file)
    print(img.dtype)
    print(img.shape)
    print(np.min(img),np.max(img))
    print('\n')

# for jpg uint8, resolution, 0-255 RGB
# for png float32, resolution, sometimes 4 instead of 3 as last element of shape, 0.0-1.0 74-242?

# with cv2 there is no 4s instead of 3s, always 0-255, last image is still 72-242



def imgToUInt8(img):
    np.issubdtype(img.dtype, np.integer)
    if np.issubdtype(img.dtype, np.unsignedinteger):
        return img
    elif np.issubdtype(img.dtype, np.floating):
        return img/255.0
    elif np.issubdtype(img.dtype, np.integer):
        return "INT->UINT not supported"

    pass

def imgToFloat(img):
    if np.issubdtype(img.dtype, np.floating):
        return img
    elif np.issubdtype(img.dtype, np.unsignedinteger):
        return (img*255).astype('uint8')
    elif np.issubdtype(img.dtype, np.integer):
        return "INT->FLOAT not supported"

for file in filenames:
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    print(file)
    # img = plt.imread(directory + file)
    img = cv2.imread(directory + file)
    R=img[:,:,0]
    G=img[:,:, 1]
    B=img[:,:, 2]
    # plt.imshow(R)
    plt.imshow(R, cmap=plt.cm.gray)
    plt.imshow(G, cmap=plt.cm.gray)
    plt.imshow(B, cmap=plt.cm.gray)
    # plt.show()

# for x in range (0,img.shape[0]):
# # for x in range (0,1):
# #     for y in range(0,1):
#     for y in range(0,img.shape[1]):
#         color = img[y,x]
#         img_RGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
#         R = color[0]
#         G = color[1]
#         B = color[2]
#
#         print(R)
#         print(G)
#         print(B)
#         # Y1=0.299 * R + 0.587 * G + 0.114 * B
#         Y2=0.2126 * R + 0.7152 * G + 0.0722 * B
import numpy as np
import matplotlib.pyplot as plt
import cv2

# Function to convert image to uint8
def imgToUInt8(img):
    if np.issubdtype(img.dtype, np.unsignedinteger):
        return img
    elif np.issubdtype(img.dtype, np.floating):
        return (np.clip(img * 255, 0, 255)).astype('uint8')
    else:
        return img  # Handle other cases if needed

# Function to convert image to float
def imgToFloat(img):
    if np.issubdtype(img.dtype, np.floating):
        return img
    elif np.issubdtype(img.dtype, np.unsignedinteger):
        return img / 255.0
    else:
        return img  # Handle other cases if needed

# Function to create and display the 3x3 grid
def image_plot_maker(img):
    # Ensure the image is in RGB format
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

    # Split the image into R, G, B channels
    R = img_rgb[:, :, 0]
    G = img_rgb[:, :, 1]
    B = img_rgb[:, :, 2]

    # Compute grayscale versions using different formulas
    Y1 = 0.299 * R + 0.587 * G + 0.114 * B
    Y2 = 0.2126 * R + 0.7152 * G + 0.0722 * B

    # Create a 3x3 grid of subplots
    fig, axes = plt.subplots(3, 3, figsize=(10, 10))
    axes = axes.flatten()  # Flatten for easy iteration

    # Titles for each subplot
    titles = [
        "Original Image",
        "Y1 Grayscale",
        "Y2 Grayscale",
        "Red Channel",
        "Green Channel",
        "Blue Channel",
        "Red Only",
        "Green Only",
        "Blue Only"
    ]

    # Display images in the grid
    for i, ax in enumerate(axes):
        match i:
            case 0:
                ax.imshow(img_rgb)  # Original image
            case 1:
                ax.imshow(Y1, cmap='gray')  # Y1 Grayscale
            case 2:
                ax.imshow(Y2, cmap='gray')  # Y2 Grayscale
            case 3:
                ax.imshow(R, cmap='gray')  # Red Channel
            case 4:
                ax.imshow(G, cmap='gray')  # Green Channel
            case 5:
                ax.imshow(B, cmap='gray')  # Blue Channel
            case 6:
                CR = img_rgb.copy()
                CR[:, :, 1] = 0  # Remove green channel
                CR[:, :, 2] = 0  # Remove blue channel
                ax.imshow(CR)  # Red Only
            case 7:
                CG = img_rgb.copy()
                CG[:, :, 0] = 0  # Remove red channel
                CG[:, :, 2] = 0  # Remove blue channel
                ax.imshow(CG)  # Green Only
            case 8:
                CB = img_rgb.copy()
                CB[:, :, 0] = 0  # Remove red channel
                CB[:, :, 1] = 0  # Remove green channel
                ax.imshow(CB)  # Blue Only

        ax.set_title(titles[i])
        ax.axis('off')  # Turn off axes

    # Adjust layout and display
    plt.tight_layout()
    plt.show()

# Main script
directory = 'IMG_INTRO/IMG_INTRO/'
filenames = ['a.png', 'B01.png', 'B02.jpg']  # Use images from category B

# Process each image
for file in filenames:
    img = cv2.imread(directory + file)
    if img is not None:
        print(f"Processing {file}...")
        image_plot_maker(img)
    else:
        print(f"Failed to load image: {file}")

import numpy as np
import matplotlib.pyplot as plt
import cv2
import pandas as pd

# Function to convert image to uint8
def imgToUInt8(img):
    if np.issubdtype(img.dtype, np.unsignedinteger):
        return img
    elif np.issubdtype(img.dtype, np.floating):
        return (img * 255).astype('uint8')
    else:
        return img  # Handle other cases if needed

# Function to convert image to float
def imgToFloat(img):
    if np.issubdtype(img.dtype, np.floating):
        return img
    elif np.issubdtype(img.dtype, np.unsignedinteger):
        return img / 255.0
    else:
        return img  # Handle other cases if needed

# Function to display and save fragments
def process_image_fragments(img, fragments, filename):
    fig, axes = plt.subplots(3, 3, figsize=(10, 10))  # Create a 3x3 grid
    axes = axes.flatten()  # Flatten for easy iteration

    for i, fragment_coords in enumerate(fragments):
        w1, k1, w2, k2 = fragment_coords
        fragment = img[w1:w2, k1:k2].copy()  # Extract the fragment

        # Convert to RGB if using OpenCV
        fragment_rgb = cv2.cvtColor(fragment, cv2.COLOR_BGR2RGB)

        # Split into R, G, B channels
        R = fragment_rgb[:, :, 0]
        G = fragment_rgb[:, :, 1]
        B = fragment_rgb[:, :, 2]

        # Compute grayscale versions
        Y1 = 0.299 * R + 0.587 * G + 0.114 * B
        Y2 = 0.2126 * R + 0.7152 * G + 0.0722 * B

        # Display the fragment and its transformations
        axes[0].imshow(fragment_rgb)
        axes[0].set_title("Original Fragment")
        axes[1].imshow(Y1, cmap='gray')
        axes[1].set_title("Y1 Grayscale")
        axes[2].imshow(Y2, cmap='gray')
        axes[2].set_title("Y2 Grayscale")
        axes[3].imshow(R, cmap='gray')
        axes[3].set_title("Red Channel")
        axes[4].imshow(G, cmap='gray')
        axes[4].set_title("Green Channel")
        axes[5].imshow(B, cmap='gray')
        axes[5].set_title("Blue Channel")

        # Display single-channel images
        CR = fragment_rgb.copy()
        CR[:, :, 1] = 0
        CR[:, :, 2] = 0
        axes[6].imshow(CR)
        axes[6].set_title("Red Only")

        CG = fragment_rgb.copy()
        CG[:, :, 0] = 0
        CG[:, :, 2] = 0
        axes[7].imshow(CG)
        axes[7].set_title("Green Only")

        CB = fragment_rgb.copy()
        CB[:, :, 0] = 0
        CB[:, :, 1] = 0
        axes[8].imshow(CB)
        axes[8].set_title("Blue Only")

        # Turn off axes for cleaner display
        for ax in axes:
            ax.axis('off')

        # Save the figure
        plt.tight_layout()
        plt.savefig(f"fragment_{filename}_{i}.png")
        plt.close()

# Main script
directory = 'IMG_INTRO/IMG_INTRO/'
filenames = ['B01.png', 'B02.jpg']  # Use images from category B

# Define fragments to extract (200x200 pixels)
fragments = [
    [100, 100, 300, 300],  # Example coordinates (w1, k1, w2, k2)
    [150, 200, 350, 400],
    [200, 300, 400, 500]
]

# Process each image
for file in filenames:
    img = cv2.imread(directory + file)
    if img is not None:
        process_image_fragments(img, fragments, file)
    else:
        print(f"Failed to load image: {file}")