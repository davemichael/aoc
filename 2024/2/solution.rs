use std::io::{self, BufRead};
use std::ops::Index;

fn parse_line(line: &str) -> Box<Vec<i32>> {
  let mut line_vals = Box::new(Vec::<i32>::new());
  for num_str in line.split(' ') {
    line_vals.push(num_str.parse::<i32>().expect(
        &("Failed parsing line: '".to_owned() + num_str + "'")));
  }
  return line_vals;
}

pub trait Len {
    fn len(&self) -> usize;
}

impl<'a, T> Len for Vec<T> {
  fn len(&self) -> usize {
      return self.len();
  }
}

// The idea here is to make a wrapper around Vec that allows you to drop out one
// index, and then use it in `is_safe` in place of a standard Vec.
struct VecDropout<'a, T> {
  vec: &'a Vec<T>,
  dropout_i: usize,
}

impl<'a, T> VecDropout<'a, T> {
  pub fn new(vec: &'a Vec<T>, dropout_i: usize) -> Self {
    Self { vec, dropout_i }
  }
}

impl<'a, T> Len for VecDropout<'a, T> {
  fn len(&self) -> usize {
    // Because we are dropping out one index, our length is one less than the
    // wrapped vector.
    return self.vec.len() - 1;
  }
}

impl<'a, T> Index<usize> for VecDropout<'a, T> {
  type Output = T;
  fn index(&self, i: usize) -> &Self::Output {
    if i < self.dropout_i { return &self.vec[i]; }
    return &self.vec[i + 1];
  }
}

fn is_safe<T: Len + Index<usize, Output = i32>>(val: &T) -> bool {
  if val.len() <= 1 { return true };
  let increasing = val[1] > val[0];
  for i in 1 .. val.len() {
    if increasing {
      if !(val[i] > val[i-1]) { return false };
    } else {
      if !(val[i-1] > val[i]) { return false };
    }
    if (val[i] - val[i-1]).abs() > 3 { return false };
  }
  return true;
}

fn main() {
  let mut q1_count = 0;
  let mut q2_count = 0;
  for line in io::stdin().lock().lines() {
    let vec = parse_line(&line.as_ref().expect("Failed reading stdio"));
    if is_safe(&*vec) {
      q1_count += 1;
      q2_count += 1;
      //println!("{}", line.unwrap());
    } else {
      for i in 0 .. vec.len() {
          if is_safe(&VecDropout::<i32>::new(&*vec, i)) {
              q2_count += 1;
              break;
          }
      }
    }
  }
  println!("{} {}", q1_count, q2_count);
}

