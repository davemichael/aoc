use std::io::{self, BufRead};

#[derive(Copy, Clone)]
enum Hand { Unset, Rock, Paper, Scissors }

#[derive(Copy, Clone)]
struct Game {
    player: Hand,
    opponent: Hand,
}

fn to_game(line: &str) -> Game {
  let mut game = Game {
    player: Hand::Unset,
    opponent: Hand::Unset
  };
  if line.contains("A") { game.opponent = Hand::Rock }
  else if line.contains("B") { game.opponent = Hand::Paper }
  else if line.contains("C") { game.opponent = Hand::Scissors }
  if line.contains("X") { game.player = Hand::Rock }
  else if line.contains("Y") { game.player = Hand::Paper }
  else if line.contains("Z") { game.player = Hand::Scissors }
  return game;
}

// Return right player's score
fn score_game(game: Game) -> i32 {
  match game {
      Game { player: Hand::Rock, opponent: Hand::Scissors } => return 6,
      Game { player: Hand::Rock, opponent: Hand::Paper } => return 0,
      Game { player: Hand::Paper, opponent: Hand::Rock } => return 6,
      Game { player: Hand::Paper, opponent: Hand::Scissors } => return 0,
      Game { player: Hand::Scissors, opponent: Hand::Paper } => return 6,
      Game { player: Hand::Scissors, opponent: Hand::Rock } => return 0,
      _ => return 3,  // Draw
  }
}

fn score_hand(hand: Hand) -> i32 {
    match hand {
        Hand::Rock => return 1,
        Hand::Paper => return 2,
        Hand::Scissors => return 3,
        Hand::Unset => std::process::abort(),
    }
}

fn score(line: &str) -> i32 {
  let game = to_game(line);
  return score_hand(game.player) + score_game(game)
}

fn main() {
    let stdin = io::stdin();
    let mut sum: i32 = 0;
    for line_result in stdin.lock().lines() {
        sum += score(&line_result.unwrap());
    }
    println!("{}", sum);
}
