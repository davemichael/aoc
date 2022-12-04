use std::io::{self, BufRead};
use std::cmp;

fn main() {
    let stdin = io::stdin();
    let mut max_cals = 0;  // Proven by inspection that there's at least one
                           // non-negative value in the input :)
    let mut sum = 0;
    for line_result in stdin.lock().lines() {
        let line = line_result.unwrap();
        if line.is_empty() {
            max_cals = cmp::max(sum, max_cals);
            sum = 0;
        } else {
          sum += line.parse::<i32>().unwrap();
        }
    }
    println!("{}", max_cals);
}
