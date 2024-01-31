pub mod serial;
pub mod display;
pub mod platform;
use std::{time::{Duration, Instant}, borrow::{Borrow, BorrowMut}, thread::{self, sleep}};

use serialport::{self, SerialPort};
use speedy2d::Window;
use std::sync::{Arc, Mutex};



fn main() {
    let ports = serialport::available_ports().unwrap();
    for p in ports {
        println!("{}", p.port_name);
    }
    let window = Window::new_centered("BallPlate", (800, 600)).unwrap();
    let platform = Arc::new(Mutex::new(platform::Platform {
        dimensions: platform::Dimensions {
            x: 214.5,
            y: 160.3,
            ballRadius: 15.0,
        },
        measurements: platform::Measurements {
            ball: platform::Position {
                x: 0.0,
                y: 0.0,
            },
            setpoint: platform::Position {
                x: 0.0,
                y: 0.0,
            },
            output: platform::Position {
                x: 0.0,
                y: 0.0,
            },
            kp: 0.0,
            ki: 0.0,
            kd: 0.0,
        },
    }));

    let display = display::Display {
        start_time: Instant::now(),
        width: 600,
        height: 400,
        platform: platform.clone(),
    };
    let port = serial::open("/dev/ttyACM0");
    // let write_port = read_port.try_clone().unwrap();
    serial::start_reader_loop(port.try_clone().unwrap(), platform.clone());
    sleep(Duration::from_secs(5)); // Wait for arduino to start after connecting to it
    println!("Setting gains");
    // serial::set_gains(port.try_clone().unwrap(), 10.0, 123.33, 0.0);
    serial::set_setpoint(port.try_clone().unwrap(), 30.0, 20.0);
    println!("Gains Set");
    window.run_loop(display);
}

