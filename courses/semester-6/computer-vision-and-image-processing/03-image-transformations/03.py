from statistics import median
import numpy as np
import matplotlib.pyplot as plt
import cv2


def image_vars(image, scale):
    original_height, original_width, channels = image.shape
    new_width = int(original_width * scale)
    new_height = int(original_height * scale)
    resized_image = np.zeros((new_height, new_width, channels), dtype=np.uint8)
    return original_height, original_width, channels, new_width, new_height, resized_image


# Nearest Neighbor Resizing
def nearest(image, scale):
    original_height, original_width, channels, new_width, new_height, resized_image = image_vars(image, scale)
    for i in range(new_height):
        for j in range(new_width):
            original_y = i * original_height / new_height
            original_x = j * original_width / new_width
            original_y = int(np.round(original_y))
            original_x = int(np.round(original_x))
            original_y = min(original_y, original_height - 1)
            original_x = min(original_x, original_width - 1)
            resized_image[i, j] = image[original_y, original_x]
    return resized_image


# Bilinear Resizing
def bilinear_base(f00, f10, f01, f11, x_f, y_f):
    result_00 = f00 * (1 - x_f)
    result_01 = f01 * (1 - x_f)
    result_10 = f10 * x_f
    result_11 = f11 * x_f
    interp_y0 = result_00 + result_10
    interp_y1 = result_01 + result_11
    result = interp_y0 * (1 - y_f) + interp_y1 * y_f
    return result


def bilinear(image, scale):
    original_height, original_width, channels, new_width, new_height, resized_image = image_vars(image, scale)
    for i in range(new_height):
        for j in range(new_width):
            x = j * (original_width - 1) / (new_width - 1)
            y = i * (original_height - 1) / (new_height - 1)
            x1, y1 = int(np.floor(x)), int(np.floor(y))
            x2, y2 = min(x1 + 1, original_width - 1), min(y1 + 1, original_height - 1)
            x_f, y_f = x - x1, y - y1
            for c in range(channels):
                f00 = image[y1, x1, c]
                f10 = image[y1, x2, c]
                f01 = image[y2, x1, c]
                f11 = image[y2, x2, c]
                resized_image[i, j, c] = bilinear_base(f00, f10, f01, f11, x_f, y_f)
    return resized_image


# Mean Resizing (modified to handle empty regions)
def mean(image, scale):
    original_height, original_width, channels, new_width, new_height, resized_image = image_vars(image, scale)
    for i in range(new_height):
        for j in range(new_width):
            x1 = int(np.floor(j * original_width / new_width))
            x2 = min(x1 + 1, original_width - 1)  # Ensure at least 1 pixel width
            y1 = int(np.floor(i * original_height / new_height))
            y2 = min(y1 + 1, original_height - 1)  # Ensure at least 1 pixel height

            for c in range(channels):
                region = image[y1:y2 + 1, x1:x2 + 1, c]  # +1 to include end pixel
                if region.size == 0:
                    resized_image[i, j, c] = 0  # Return 0 for empty regions
                else:
                    resized_image[i, j, c] = np.mean(region)
    return resized_image


# Median Resizing (modified to handle empty regions)
def median(image, scale):
    original_height, original_width, channels, new_width, new_height, resized_image = image_vars(image, scale)
    for i in range(new_height):
        for j in range(new_width):
            x1 = int(np.floor(j * original_width / new_width))
            x2 = min(x1 + 1, original_width - 1)  # Ensure at least 1 pixel width
            y1 = int(np.floor(i * original_height / new_height))
            y2 = min(y1 + 1, original_height - 1)  # Ensure at least 1 pixel height

            for c in range(channels):
                region = image[y1:y2 + 1, x1:x2 + 1, c]  # +1 to include end pixel
                if region.size == 0:
                    resized_image[i, j, c] = 0  # Return 0 for empty regions
                else:
                    resized_image[i, j, c] = np.median(region)
    return resized_image


# Weighted Mean Resizing (modified to handle empty regions)
def weight_mean(image, scale):
    original_height, original_width, channels, new_width, new_height, resized_image = image_vars(image, scale)
    for i in range(new_height):
        for j in range(new_width):
            x1 = int(np.floor(j * original_width / new_width))
            x2 = min(x1 + 1, original_width - 1)  # Ensure at least 1 pixel width
            y1 = int(np.floor(i * original_height / new_height))
            y2 = min(y1 + 1, original_height - 1)  # Ensure at least 1 pixel height

            for c in range(channels):
                region = image[y1:y2 + 1, x1:x2 + 1, c]  # +1 to include end pixel
                if region.size == 0:
                    resized_image[i, j, c] = 0  # Return 0 for empty regions
                else:
                    weights = np.ones_like(region)
                    weighted_sum = np.sum(region * weights)
                    total_weight = np.sum(weights)
                    resized_image[i, j, c] = weighted_sum / total_weight if total_weight != 0 else 0
    return resized_image
# Edge Detection using Canny
def detect_edges(image):
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray_image, 100, 200)
    return edges

def process_image(image, filename, scales=[0.05, 0.1, 1.25, 2]):
    results = []
    for scale in scales:
        print(f"Processing {filename} at {scale * 100}% scale")

        # Create fragments for big images
        fragments = []
        if scale < 1 and image.shape[0] > 1000:
            h, w = image.shape[:2]
            fragments = [
                image[:h//3, :w//3],    # Top-left
                image[:h//3, w//3:w*2//3],  # Top-center
                image[h//3:h*2//3, :w//3]   # Middle-left
            ]

        # Always use all methods regardless of scale
        methods = {

            'Mean': mean(image, scale),
            'Median': median(image, scale),
            'Weighted_Mean': weight_mean(image, scale)
        }

        # Process fragments if any
        frag_results = []
        for i, frag in enumerate(fragments):
            frag_methods = {
                f'Frag{i+1}_Mean': mean(frag, scale),
                f'Frag{i+1}_Median': median(frag, scale),
                f'Frag{i+1}_Weighted': weight_mean(frag, scale)
            }
            frag_results.append(frag_methods)

        # Rest of the function remains the same...
        edges = {k: detect_edges(v) for k, v in methods.items()}
        frag_edges = []
        for frag in frag_results:
            frag_edges.append({k: detect_edges(v) for k, v in frag.items()})

        results.append({
            'scale': scale,
            'methods': methods,
            'edges': edges,
            'fragments': frag_results,
            'fragment_edges': frag_edges
        })

    return results
def visualize_results(results, filename):
    for result in results:
        scale = result['scale']
        is_downscaling = scale < 1

        # Show main image results
        plt.figure(figsize=(15, 10 if is_downscaling else 5))
        for i, (name, img) in enumerate(result['methods'].items()):
            plt.subplot(2, 3 if is_downscaling else 2, i + 1)
            plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
            plt.title(f"{name}\nScale: {scale * 100}%")
        plt.tight_layout()
        plt.show()

        # Show edges
        plt.figure(figsize=(15, 10 if is_downscaling else 5))
        for i, (name, edge) in enumerate(result['edges'].items()):
            plt.subplot(2, 3 if is_downscaling else 2, i + 1)
            plt.imshow(edge, cmap='gray')
            plt.title(f"Edges - {name}\nScale: {scale * 100}%")
        plt.tight_layout()
        plt.show()

        # Show fragments if any
        if result['fragments']:
            for frag_idx, frag in enumerate(result['fragments']):
                plt.figure(figsize=(15, 10))
                for i, (name, img) in enumerate(frag.items()):
                    plt.subplot(2, 3, i + 1)
                    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
                    plt.title(f"Fragment {frag_idx + 1} - {name}\nScale: {scale * 100}%")
                plt.tight_layout()
                plt.show()

                plt.figure(figsize=(15, 10))
                for i, (name, edge) in enumerate(result['fragment_edges'][frag_idx].items()):
                    plt.subplot(2, 3, i + 1)
                    plt.imshow(edge, cmap='gray')
                    plt.title(f"Fragment {frag_idx + 1} Edges - {name}")
                plt.tight_layout()
                plt.show()


def main():
    # Small images (4)
    small_files = ['SMALL_0004.jpg', 'SMALL_0007.jpg', 'SMALL_0009.jpg', 'SMALL_0001.tif'][:4]
    for file in small_files:
        img = cv2.imread('IMG_SMALL/' + file)
        if img is not None:
            results = process_image(img, file)
            visualize_results(results, file)
    #
    # # Big images (2)
    # big_files = ['BIG_0001.jpg', 'BIG_0004.png'][:2]
    # for file in big_files:
    #     img = cv2.imread('IMG_BIG/' + file)
    #     if img is not None:
    #         results = process_image(img, file, scales=[0.05, 0.1, 0.3])  # Downscaling only
    #         visualize_results(results, file)


if __name__ == "__main__":
    main()