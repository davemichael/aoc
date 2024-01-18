use std::io::{self, BufRead};
use std::collections::HashMap;

fn count_draw(draw: &str) -> Box<HashMap<String, i32>> {
  let mut counts = Box::new(HashMap::from([]));
  let color_counts = draw.split(',');
  for color_count in color_counts {
    let Some((count, color)) = color_count.trim().split_once(' ')
        else { panic!("failed to split color counts: {}", color_count); };
    *counts.entry(color.to_owned()).or_default() +=
        count.parse::<i32>().unwrap();
    // println!("color {} count {}", color, *counts.entry(color.to_owned()).or_default());
  }
  // println!("draw: {}", draw);
  return counts;
}

fn draw_is_valid(counts: &mut HashMap<String, i32>) -> bool {
  if *counts.entry("red".to_owned()).or_default() > 12 { return false; }
  if *counts.entry("green".to_owned()).or_default() > 13 { return false; }
  if *counts.entry("blue".to_owned()).or_default() > 14 { return false; }
  return true;
}

fn line_is_valid(line: &str) -> bool {
  let draws = line.split(';');
  for draw in draws {
    if !draw_is_valid(&mut *count_draw(draw)) { return false; }
  }
  return true;
}

fn return_game_if_possible(line: &str) -> i32 {
  let Some((game_str, draws)) = line.split_once(':')
      else { panic!("failed to parse game line: {}", line); };
  if line_is_valid(draws) {
    // println!("game is impossible: {}", game_str);
    let num = game_str.split_once(' ').unwrap().1.parse::<i32>().unwrap();
    // println!("gamenum: {}", num);
    return num;
  }
  return 0;
}

fn main() {
  let stdin = io::stdin();
  let mut sum = 0;
  for line in stdin.lock().lines() {
    sum += return_game_if_possible(&line.unwrap());
  }
  println!("{}", sum);
}

