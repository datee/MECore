package me.math;

import me.internal.math.BaseVec4;

// I know the Vector2 being a Vector4 under the hood is super cursed but its for SIMD.

/**
    A two-dimensional vector.
**/
@:notNull
@:forward(x, y, Set, Copy)
abstract Vector2(BaseVec4) from BaseVec4 to BaseVec4 {
    public inline function new(x: Single, y: Single) {
        this = new BaseVec4(x, y, 1, 1);
    }

    // CONSTRUCTORS
    public inline static function Zero(): Vector2 {
        return new Vector2(0, 0);
    }

    public inline static function One(): Vector2 {
        return new Vector2(1, 1);
    }

    // COMPONENT
    @:commutative
    @:op(A + B)
    public inline function Add(other: Vector2): Vector2 {
        return new Vector2(this.x + other.x, this.y + other.y);
    }

    @:commutative
    @:op(A - B)
    public inline function Subtract(other: Vector2): Vector2 {
        return new Vector2(this.x - other.x, this.y - other.y);
    }

    @:commutative
    @:op(A * B)
    public inline function MultiplyComp(other: Vector2): Vector2 {
        return new Vector2(this.x * other.x, this.y * other.y);
    }

    @:op(A / B)
    public inline function DivideComp(other: Vector2): Vector2 {
        return new Vector2(this.x / other.x, this.y / other.y);
    }

    // SCALE
    @:commutative
    @:op(A * B)
    public inline function MultiplyScale(other: Single): Vector2 {
        return new Vector2(this.x * other, this.y * other);
    }

    @:op(A / B)
    public inline function DivideScale(other: Single): Vector2 {
        return new Vector2(this.x / other, this.y / other);
    }

    // INDEXER
    @:op([])
    public inline function IndexRead(index: Int): Single {
        if (index == 0) return this.x;
        if (index == 1) return this.y;
        throw 'Invalid index when reading Vector2';
    }

    @:op([])
    public inline function IndexWrite(index: Int, value: Single): Void {
        if (index == 0) this.x = value;
        if (index == 1) this.y = value;
        throw 'Invalid index when writing to Vector2';
    }

    // STRING
    @:to
    public inline function ToString(): String {
        return '(${this.x}, ${this.y})';
    }
}
