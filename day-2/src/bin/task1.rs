use std::fs;

fn main() {
    let contents = fs::read_to_string("input.txt").expect("Something went wrong reading the file");
    let lines = contents.trim().lines();

    let mut depth = 0;
    let mut position = 0;

    for line in lines {
        let elements: Vec<&str> = line.split(" ").collect();
        let magnitude = elements[1].parse::<i32>().unwrap();

        match elements[0] {
            "forward" => position += magnitude,
            "down" => depth += magnitude,
            "up" => depth -= magnitude,
            _ => panic!("Unknown action: {}", elements[0]),
        }
    }

    println!("Position: {}, Depth: {}", position, depth);
    println!("Score: {}", position * depth);
}
