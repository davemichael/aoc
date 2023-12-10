use std::io::{self, BufRead};
use std::collections::HashMap;

// return valid strings that represent a numeral (0 is absent)
// There's not a nice way I could find to make a static dictionary/hashmap.
// We could have done a lazy static HashMap apparently, but...  not worth it.
//
// Also have to Box because HashMap's size can't be known at compile time.
// Presumably / hopefully this acts more-or-less like a std::move.
fn numerals() -> Box<HashMap<&'static str, i32>> {
  return Box::new(HashMap::from([
      ("1", 1), ("2", 2), ("3", 3), ("4", 4), ("5", 5), ("6", 6), ("7", 7),
      ("8", 8), ("9", 9),
      ("one", 1), ("two", 2), ("three", 3), ("four", 4), ("five", 5),
      ("six", 6), ("seven", 7), ("eight", 8), ("nine", 9)])
  );
}

fn find_first_digit(line: &str) -> i32 {
  let mut best_val = None;
  let mut best_i = None;

  for (s, val) in *numerals() {
    let result = line.find(s);
    if result != None {
      let i = result.unwrap();
      if best_i == None || i < best_i.unwrap() {
        best_i = Some(i);
        best_val = Some(val);
      }
    }
  }
  assert!(best_val != None, "failed to find first num in {}", line);
  return best_val.unwrap();
}

fn find_last_digit(line: &str) -> i32 {
  let mut best_val = None;
  let mut best_i = None;

  for (s, val) in *numerals() {
    let result = line.rfind(s);
    if result != None {
      let i = result.unwrap();
      if best_i == None || i > best_i.unwrap() {
        best_i = Some(i);
        best_val = Some(val);
      }
    }
  }
  assert!(best_val != None, "failed to find last num in {}", line);
  return best_val.unwrap();
}

fn parse_line(line: &str) -> i32 {
  let first_digit = find_first_digit(line);
  let last_digit = find_last_digit(line);
  return first_digit * 10 + last_digit;
}

fn main() {
  let stdin = io::stdin();
  let mut sum = 0;
  for line in stdin.lock().lines() {
    sum += parse_line(&line.unwrap());
  }
  println!("{}", sum);
}

