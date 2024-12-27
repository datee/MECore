package me.math;

import me.math.BaseVec3;

/**
    A three-dimensional vector.
**/
@:notNull
@:forward(x, y, z, Set, Copy)
@:forward.new
abstract Vector3(BaseVec3) from BaseVec3 to BaseVec3 {
    // CONSTRUCTORS
    public inline static function Zero(): Vector3 {
        return new BaseVec3(0, 0, 0);
    }

    public inline static function One(): Vector3 {
        return new BaseVec3(1, 1, 1);
    }

    // COMPONENT
    @:commutative
    @:op(A + B)
    public inline function Add(other: Vector3): Vector3 {
        return new Vector3(this.x + other.x, this.y + other.y, this.z + other.z);
    }

    @:commutative
    @:op(A - B)
    public inline function Subtract(other: Vector3): Vector3 {
        return new Vector3(this.x - other.x, this.y - other.y, this.z - other.z);
    }

    @:commutative
    @:op(A * B)
    public inline function MultiplyComp(other: Vector3): Vector3 {
        return new Vector3(this.x * other.x, this.y * other.y, this.z * other.z);
    }

    @:op(A / B)
    public inline function DivideComp(other: Vector3): Vector3 {
        return new Vector3(this.x / other.x, this.y / other.y, this.z / other.z);
    }

    // SCALE
    @:commutative
    @:op(A * B)
    public inline function MultiplyScale(other: Single): Vector3 {
        return new Vector3(this.x * other, this.y * other, this.z * other);
    }

    @:op(A / B)
    public inline function DivideScale(other: Single): Vector3 {
        return new Vector3(this.x / other, this.y / other, this.z / other);
    }

    // INDEXER
    @:op([])
    public inline function IndexRead(index: Int) {
        if (index == 0) return this.x;
        if (index == 1) return this.y;
        if (index == 2) return this.z;
        throw 'Invalid index when reading Vector3';
    }

    @:op([])
    public inline function IndexWrite(index: Int, value: Single) {
        if (index == 0) return this.x = value;
        if (index == 1) return this.y = value;
        if (index == 2) return this.z = value;
        throw 'Invalid index when writing to Vector3';
    }

    // STRING
    @:to
    public inline function ToString(): String {
        return '(${this.x}, ${this.y}, ${this.z})';
    }
}
