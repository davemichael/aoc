use std::io::{self, BufRead};

fn parse_lines(line: &str, left: &mut Vec<i32>, right: &mut Vec<i32>) {
  let Some((loc_id_left, loc_id_right)) = line.split_once("   ")
      else { panic!("failed to parse line: {}", line); };
  left.push(loc_id_left.parse::<i32>().unwrap());
  right.push(loc_id_right.parse::<i32>().unwrap());
  return;
}

fn main() {
  let stdin = io::stdin();
  let mut left_vec = Vec::<i32>::new();
  let mut right_vec = Vec::<i32>::new();
  for line in stdin.lock().lines() {
    parse_lines(&line.unwrap(), &mut left_vec, &mut right_vec);
  }
  assert!(left_vec.len() == right_vec.len());
  left_vec.sort();
  right_vec.sort();
  let mut sum = 0;
  for i in 0..left_vec.len() {
    sum += (left_vec[i] - right_vec[i]).abs();
  }
  println!("{}", sum);
}

