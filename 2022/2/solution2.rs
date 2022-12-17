use std::io::{self, BufRead};

#[derive(Copy, Clone)]
enum Hand { Unset, Rock, Paper, Scissors }

#[derive(Copy, Clone)]
enum Result { Win, Lose, Draw }

#[derive(Copy, Clone)]
struct Game {
    player: Hand,
    opponent: Hand,
}

fn parse_line(line: &str) -> (Hand, Result) {
  let mut opponent = Hand::Unset;
  if line.contains("A") { opponent = Hand::Rock }
  else if line.contains("B") { opponent = Hand::Paper }
  else if line.contains("C") { opponent = Hand::Scissors }
  if line.contains("X") { return (opponent, Result::Lose) }
  else if line.contains("Y") { return (opponent, Result::Draw) }
  else if line.contains("Z") { return (opponent, Result::Win) }

  println!("{}", line);
  std::process::abort();
}

fn hand_to_play(opponent_in: Hand, desired_result: Result) -> Hand {
  match (opponent_in, desired_result) {
      (Hand::Rock, Result::Win) => return Hand::Paper,
      (Hand::Paper, Result::Win) => return Hand::Scissors,
      (Hand::Scissors, Result::Win) => return Hand::Rock,
      (Hand::Rock, Result::Lose) => return Hand::Scissors,
      (Hand::Paper, Result::Lose) => return Hand::Rock,
      (Hand::Scissors, Result::Lose) => return Hand::Paper,
      _ => return opponent_in,
  }
}

fn to_game(opponent_in: Hand, desired_result: Result) -> Game {
  return Game {
    opponent: opponent_in,
    player: hand_to_play(opponent_in, desired_result),
  }
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
  let (opponent, desired_result) = parse_line(line);
  let game = to_game(opponent, desired_result);
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
