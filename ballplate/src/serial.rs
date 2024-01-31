use std::str;
use std::{borrow::{Borrow, BorrowMut}, error::Error, io, ops::Deref, sync::{Arc, Mutex}, thread::{self, sleep}, time::Duration};

use serialport::SerialPort;

use crate::platform::{self, Measurements, Position};

fn read_until_signature(port: &mut Box<dyn SerialPort>, signature: Vec<u8>) -> Result<(), io::Error> {
    let mut buf: [u8; 1] = [0; 1];
    let mut values_read = vec![0;signature.len()];
    loop {
        match port.read_exact(&mut buf) {
            Ok(_) => {
                values_read.push(buf[0]);
                if values_read.len() > signature.len() {
                    values_read.remove(0);
                }
                if values_read == signature {
                    return Ok(());
                }
            },
            Err(e) => {
                eprintln!("Error reading one byte: {}", e);
                continue;
            },
        }
    }

}

fn read_raw_data(port: &mut Box<dyn SerialPort>) {
    loop {
        let size = port.bytes_to_read().unwrap();
        let mut buf: Vec<u8> = vec![0; size as usize];
        if size == 0 { continue }
        match port.read_exact(&mut buf) {
            Ok(_)=> {
                println!("Raw data: {}", str::from_utf8(&buf).unwrap());
            },
            Err(e) => {
                // eprintln!("Error reading raw data: {}", e);
            },
        }
    }
}

fn read_packet(port: &mut Box<dyn SerialPort>) -> Result<Vec<u8>, io::Error> {
    let mut packet: Vec<u8> = vec![0; 64];
    read_until_signature(port, [0xFF, 0xFF].to_vec())?; // Start byte
    match port.read_exact(&mut packet) {
        Ok(_) => {
            // println!("Packet: {:X?}", packet);
            Ok(packet)
        },
        Err(e) => Err(e),
    }
}

pub fn read_f64_vector(package: Vec<u8>) -> Vec<f64> {
    let n_values = package.len() / 8;
    let mut values: Vec<f64> = vec![0.0; n_values];
    for i in 0..n_values {
        values[i] = f64::from_le_bytes([package[i*8], package[i*8+1], package[i*8+2], package[i*8+3], package[i*8+4], package[i*8+5], package[i*8+6], package[i*8+7]]);
    }
    return values;
}

pub fn read_f32_vector(package: Vec<u8>) -> Vec<f32> {
    let n_values = package.len() / 4;
    let mut values: Vec<f32> = vec![0.0; n_values];
    for i in 0..n_values {
        values[i] = f32::from_le_bytes([package[i*4], package[i*4+1], package[i*4+2], package[i*4+3]]);
    }
    return values;
}

pub fn read_serial(port: &mut Box<dyn SerialPort>, mut callback: Box<dyn FnMut(Measurements)>) {
    loop {
        match read_packet(port) {
            Ok(packet) => {
                let values = read_f32_vector(packet);
                let meas = Measurements {
                    ball: Position {
                        x: values[0],
                        y: values[1],
                    },
                    setpoint: Position {
                        x: values[2],
                        y: values[3],
                    },
                    output: Position {
                        x: values[4],
                        y: values[5],
                    },
                    kp: values[6],
                    ki: values[7],
                    kd: values[8],
                };
                callback(meas);
            },
            Err(e) => {
                eprintln!("Error reading packet: {}", e)
            }
        }
    }
}

pub fn write_serial(mut port: Box<dyn SerialPort>, content: Vec<u8>) {
    match port.write(&content) {
        Ok(_) => (),
        Err(e) => eprintln!("Error writing to serial: {}", e),
    }
}


pub fn open(path: &str) -> Box<dyn SerialPort> {
    let port = serialport::new(path, 115200)
    .timeout(Duration::from_millis(10))
    .open();
    return port.unwrap();
}

pub fn start_reader_loop(mut port: Box<dyn SerialPort>, platform: Arc<Mutex<platform::Platform>>){
    thread::spawn(move || {
        sleep(Duration::from_secs(2));
        // read_serial(&mut port, Box::new(move |measurements: Measurements| {
        //     let mut plat = platform.lock().unwrap();
        //     plat.measurements = measurements;
        //     println!("{:?}", plat.measurements);
        // }));
        read_raw_data(&mut port);

    });
}


pub fn set_gains(port: Box<dyn SerialPort>, kp: f32, ki: f32, kd: f32) {
    let command = "SG";
    let mut content: Vec<u8> = vec![0x00; 64];
    content[0] = 0xFF;
    content[1..3].copy_from_slice(command.as_bytes());
    content[3..7].copy_from_slice(&kp.to_le_bytes());
    content[7..11].copy_from_slice(&ki.to_le_bytes());
    content[11..15].copy_from_slice(&kd.to_le_bytes());
    write_serial(port, content);
}

pub fn set_setpoint(port: Box<dyn SerialPort>, x: f32, y: f32) {
    let command = "SS";
    let mut content: Vec<u8> = vec![0x00; 64];
    content[0] = 0xFF;
    content[1..3].copy_from_slice(command.as_bytes());
    content[3..7].copy_from_slice(&x.to_le_bytes());
    content[7..11].copy_from_slice(&y.to_le_bytes());
    write_serial(port, content);
}
