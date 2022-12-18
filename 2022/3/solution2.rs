use std::io::{self, BufRead};

// ASCII has uppercase first, the problem has lowercase lower-priority...
// we'll index lower-first, then upper, for convenience elsewhere.
fn to_index(c: u8) -> usize {
    let result: usize;
    if c < 97 { result = (c as usize) - 65 + 26 }
    else { result = (c as usize) - 97 }
    if result >= 52 {
        println!("{}", c);
        std::process::abort();
    }
    return result;
}

fn parse_line(line: &str) -> [bool; 52] {
  let mut result = [false; 52];
  let str_bytes = line.as_bytes();
  for i in 0..str_bytes.len() {
    result[to_index(str_bytes[i])] = true;
  }
  return result;
}

fn intersect(left: &[bool; 52], right: &[bool; 52]) -> [bool; 52] {
  let mut result = [false; 52];
  for i in 0..52 {
    result[i] = left[i] && right[i];
  }
  return result;
}

fn main() {
    let stdin = io::stdin();
    let mut sum = 0;
    let mut group: [[bool; 52]; 3] = [[false; 52]; 3];
    let mut group_index = 0;
    for line in stdin.lock().lines() {
      group[group_index] = parse_line(&line.as_ref().unwrap());
      group_index += 1;
      if group_index == 3 {
          group_index = 0;
          let intersection = intersect(&group[0], &intersect(&group[1], &group[2]));
          for i in 0..52 {
              if intersection[i] { sum += 1 + i; }
          }
      }
    }
    println!("{}", sum);
}
