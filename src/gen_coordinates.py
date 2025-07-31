#!/usr/bin/env python3
import random
from pathlib import Path

def generate_sandpile_tsv(filename, width, height, max_grains=4, empty_prob=0.3):
    data = []
    center_x, center_y = width // 2, height // 2
    
    for y in range(height):
        for x in range(width):
            distance_to_center = ((x - center_x)**2 + (y - center_y)**2)**0.5
            if random.random() < empty_prob * (distance_to_center / (width/2)):
                continue
                
            grains = random.randint(1, max_grains)
            data.append(f"{x}\t{y}\t{grains}\n")
    
    with open(filename, 'w') as f:
        f.writelines(data)
    print(f"Generated {filename} with {len(data)} cells")

if __name__ == "__main__":
    generate_sandpile_tsv("sandpile_10x10.tsv", 10, 10)
    generate_sandpile_tsv("sandpile_50x50.tsv", 50, 50)
    generate_sandpile_tsv("sparse_sandpile.tsv", 20, 20, empty_prob=0.7)