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

fn parse_left(line: &str) -> [bool; 52] {
  let mut result = [false; 52];
  let str_bytes = line.as_bytes();
  let end = str_bytes.len() / 2; // length is even; end is one-past-last
  for i in 0..end {
    result[to_index(str_bytes[i])] = true;
  }
  return result;
}

fn find_common(line: &str, left_word: &[bool; 52]) -> usize {
  let str_bytes = line.as_bytes();
  let begin = str_bytes.len() / 2; // length is even 
  let end = str_bytes.len();
  for i in begin..end {
    if left_word[to_index(str_bytes[i])] {
        return to_index(str_bytes[i]);
    }
  }
  println!("{}", line);
  std::process::abort();
}

fn main() {
    let stdin = io::stdin();
    let mut sum = 0;
    for line_result in stdin.lock().lines() {
      let comp1 = parse_left(&line_result.as_ref().unwrap());
      let c = find_common(&line_result.as_ref().unwrap(), &comp1);
      sum += c + 1;
    }
    println!("{}", sum);
}
