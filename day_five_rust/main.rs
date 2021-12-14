use std::io::{self, BufRead};
use std::cmp::max;

struct Line {
    x1: i16,
    x2: i16,
    y1: i16,
    y2: i16,
}

impl Line {
    fn conv(v: &Vec<u8>) -> i16 {
        v.into_iter()
         .map(|c| *c as i16 - '0' as i16)
         .fold(0 as i16, |a, b| a * 10 + b)
    }

    fn next_number<T: BufRead>(separator: u8, buffer_b: &mut T) ->
      io::Result<i16> {
        let mut num = vec![];
        buffer_b.read_until(separator, &mut num)?;
        num.pop();
        Ok(Line::conv(&num))
    }

    fn new(buffer: &String) -> io::Result<Line> {
        let mut buffer_b = buffer.as_bytes();
        let x1 = Line::next_number(b',', &mut buffer_b)?;
        let y1 = Line::next_number(b' ', &mut buffer_b)?;

        let mut tmp = vec![];
        buffer_b.read_until(b' ', &mut tmp)?;

        let x2 = Line::next_number(b',', &mut buffer_b)?;
        let y2 = Line::next_number(b'\n', &mut buffer_b)?;

        Ok(Line { x1, y1, x2, y2, })
    }
}

#[allow(non_snake_case)]
fn main() -> io::Result<()> {
    let mut buffer = String::new();
    let stdin = io::stdin();

    let size = 1000;
    let mut tab = vec![vec![0 as u16; size]; size].into_boxed_slice();

    // I miss list comprehensions :(
    let dxy: Vec<(i16, i16)> =
        vec![(-1,-1), (-1,0), (-1,1),
             (0, -1),         (0, 1),
             (1, -1), (1, 0), (1,1)];

    loop {
        let bits_read = stdin.read_line(&mut buffer)?;
        if bits_read <= 0 {
            break;
        }

        let line = Line::new(&mut buffer)?;
        buffer.clear();

        let M = max((line.x1 - line.x2).abs(), (line.y1 - line.y2).abs());
        let mut c_dx: i16 = 0;
        let mut c_dy: i16 = 0;
        let mut c_t: i16 = 0;
        for (dx, dy) in &dxy {
            for t in 1 ..= M {
                if line.x1 + t * dx == line.x2 && line.y1 + t * dy == line.y2 {
                    c_dx = *dx;
                    c_dy = *dy;
                    c_t = t;
                    break;
                }
            }
        }
        for t in 0 ..= c_t {
            let row = (line.x1 + t * c_dx) as usize;
            let col = (line.y1 + t * c_dy) as usize;
            tab[row][col] += 1;
        }
    }

    let mut answer: u32 = 0;
    tab.into_iter().for_each(|row| {
        for val in row {
            if *val >= 2 {
                answer += 1;
            }
        }
    });
    println!("{}", answer);
    Ok(())
}
