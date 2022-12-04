use std::collections::BinaryHeap;
use std::io::{self, BufRead};
use std::cmp::Reverse;

// Let's play with traits...
trait Shrinkable {
    // Shrink `self` to at-most `n` elements.
    fn pop_to_size(&mut self, n: usize);
}

impl<U: Ord> Shrinkable for BinaryHeap<U> {
    fn pop_to_size(&mut self, n: usize) {
        while self.len() > n {
            self.pop();
        }
    }
}

// Sigh. Have to implement Sum over Reverse, it's not defined already.
// Sigh. Reverse is not in this Crate, so I can't implement traits for it.
// Sigh. This seems to be impossible.
/*use Reverse<T> as MyReverse<T>;
//type MyReverse<T> = Reverse<T>; // loses all constructors ?!?
impl<T> Sum<MyReverse<T>> for MyReverse<T> {
    fn sum<I>(iter: I) -> MyReverse<T>
    where
        I: Iterator<Item = MyReverse<T>>,
    {
        let sum = iter.reduce(|sum, val| sum += T::from(val));
        return MyReverse(sum);
    }
}*/

fn main() {
    let stdin = io::stdin();
    let mut sum: i32 = 0;
    // We'll push up to 4 and then pop to 3.
    let mut fattest_elves = BinaryHeap::with_capacity(4);
    for line_result in stdin.lock().lines() {
        let line = line_result.unwrap();
        if line.is_empty() {
            // Use Reverse, because we need min-heap so that we always retain
            // the largeste 3.
            fattest_elves.push(Reverse(sum));
            // println!("{}", fattest_elves.peek().unwrap());
            fattest_elves.pop_to_size(3);
            // println!("{}", sum);
            sum = 0;
        } else {
          sum += line.parse::<i32>().unwrap();
        }
    }
    // Sum is not defined for Reverse
    // let final_sum: i32 = fattest_elves.iter().sum();
    // And this reduce way isn't working; how the hell do you unwrap a Reverse?
    /*
    let final_sum = fattest_elves.iter()
        .reduce(|sum: i32, val: Reverse<i32>|->i32 {
            sum += val.into_inner();
        });
        */
    let mut final_sum: i32 = 0;
    while !fattest_elves.is_empty() {
        let val = if let Some(Reverse(val)) = fattest_elves.pop() {
            val } else { 0 };
        final_sum += val;
    }
    println!("{}", final_sum);
}
