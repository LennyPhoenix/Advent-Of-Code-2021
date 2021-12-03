with open("inputs.txt") as f:
    lines = f.readlines()

depths = list(map(int, lines))

counter = 0
previous = None

for i in range(len(depths)-2):
    total = depths[i] + depths[i+1] + depths[i+2]
    if previous is not None and total > previous:
        counter += 1
    previous = total

print(f"Score: {counter}")
