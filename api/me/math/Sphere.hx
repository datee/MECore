package me.math;

class Sphere {
    public var radius: Single;

    public function new(radius: Single) {
        this.radius = radius;
    }

    public static function Unit(): Sphere {
        return new Sphere(1);
    }
}
