use std::io::{self, BufRead};
use std::collections::HashMap;

fn parse_line(line: &str) -> (i32, i32) {
  let Some((loc_id_left, loc_id_right)) = line.split_once("   ")
      else { panic!("failed to parse line: {}", line); };
  return (loc_id_left.parse::<i32>().expect(
              &("Failed parsing left: '".to_owned() + loc_id_left + "'")),
          loc_id_right.parse::<i32>().expect(
              &("Failed parsing right: '".to_owned() + loc_id_right + "'")));
}

// Return a vector containing all integers from the left and a hash map of
// value->count for the right list.
fn parse_lines<T: BufRead>(input: T) -> (Box<Vec<i32>>, Box<HashMap<i32, i32>>) {
  let mut left_vec = Box::new(Vec::<i32>::new());
  let mut right_map = Box::new(HashMap::<i32, i32>::new());
  for line in input.lines() {
    let (left, right) = parse_line(&line.unwrap());
    left_vec.push(left);
    *right_map.entry(right).or_default() += 1;
  }
  return (left_vec, right_map);
}


fn main() {
  let (left_vec, right_map) = parse_lines(io::stdin().lock());
  let mut sum = 0;
  for i in 0..left_vec.len() {
    // Notes on learning rust......  why do I have to borrow these two parameters?
    // They are simply i32 and I'd rather they be passed by value.
    // move isn't right either. Is this just how it works?
    sum += left_vec[i] * right_map.get(&left_vec[i]).unwrap_or(&0);
  }
  println!("{}", sum);
}

