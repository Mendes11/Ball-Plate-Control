use std::{time::Instant, sync::{Arc, Mutex}};

use speedy2d::{window::WindowHandler, color::Color, dimen::Vec2, shape::Rectangle};

use crate::platform::{self, Platform};


pub struct Display {
    pub start_time: Instant,
    pub width: u32,
    pub height: u32,
    pub platform: Arc<Mutex<platform::Platform>>,
}

impl Display {
    fn mm_to_px_pos_x(&self, limit: f32, mm: f32) -> f32 {
        return (self.width as f32 * mm) / limit;
    }

    fn mm_to_px_pos_y(&self, limit: f32, mm: f32) -> f32 {
        return (self.height as f32 * mm) / limit;
    }
}

impl WindowHandler for Display {
    fn on_draw(&mut self, helper: &mut speedy2d::window::WindowHelper<()>, graphics: &mut speedy2d::Graphics2D) {
        graphics.clear_screen(Color::BLACK);
        let elapsed_secs = self.start_time.elapsed().as_secs_f32();
        let platform = self.platform.lock().unwrap();
        let start_x = (self.width as f32) / 2.0;
        let start_y = (self.height as f32) / 2.0;

        graphics.draw_rectangle(Rectangle::new(Vec2::new(0.0, 0.0), Vec2::new(self.width as f32, self.height as f32)), Color::GRAY);

        let x_pos = self.mm_to_px_pos_x(platform.dimensions.x, platform.measurements.ball.x);
        let y_pos = self.height as f32 - self.mm_to_px_pos_y(platform.dimensions.y, platform.measurements.ball.y);

        let position = Vec2::new(x_pos, y_pos);
        graphics.draw_circle(position, platform.dimensions.ballRadius, Color::RED);

        helper.request_redraw();
    }
}

impl Display {

    // TODO: Doesn't work
    // pub fn run(&mut self) {
    //     self.window.run_loop(self);
    // }
}

// impl Display {
//     fn new(width: u32, height: u32, platform_width: f32, platform_height: f32) -> Display {
//         let mut canvas = Canvas::new(width, height);
//         let startX = (width as f32 - platform_width) / 2.0;
//         let startY = (height as f32 - platform_height) / 2.0;

//         let mut rect = Drawing::new()
//             .with_shape(Shape::Rectangle{width: platform_width as u32, height: platform_height as u32})
//             .with_xy((width as f32 - platform_width) / 2.0, (height as f32 - platform_height) / 2.0)
//             .with_style(Style::stroked(5, Color::gray(255)));

//         let mut ball = Drawing::new()
//             .with_shape(Shape::Circle { radius: 17 })
//             .with_xy(startX + platform_width / 2.0, startY + platform_height / 2.0)
//             .with_style(Style::filled(RGB::new(255, 0, 0)));

//         canvas.display_list.add(rect);
//         canvas.display_list.add(ball);
//         Display {
//             canvas,
//             platform: rect,
//             ball: ball,
//         }
//     }

//     fn update(&mut self, x: f32, y: f32) {
//         render::
//     }
// }



