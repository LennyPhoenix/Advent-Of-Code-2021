with open("inputs.txt") as f:
    lines = f.readlines()

depths = map(int, lines)

previous = None
counter = 0
for depth in depths:
    if previous is not None and depth > previous:
        counter += 1
    previous = depth

print(f"Score: {counter}")
