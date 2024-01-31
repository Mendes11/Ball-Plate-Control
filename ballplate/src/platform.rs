pub struct Dimensions {
    pub x: f32,
    pub y: f32,
    pub ballRadius: f32,
}

#[derive(Debug)]
pub struct Position {
    pub x: f32,
    pub y: f32
}

pub struct Ball {
    pub r: f32, // radius
    pub x: f32,
    pub y: f32,
}

#[derive(Debug)]
pub struct Measurements {
    pub ball: Position,
    pub setpoint: Position,
    pub output: Position,
    pub kp: f32,
    pub ki: f32,
    pub kd: f32,
}

pub struct Platform {
    // Dimensions
    pub dimensions: Dimensions,
    pub measurements: Measurements,
}

