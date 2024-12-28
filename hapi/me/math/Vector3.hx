package me.math;

import me.math.BaseVec4;

// I know the Vector3 being a Vector4 under the hood is super cursed but its for SIMD.

/**
    A three-dimensional vector.
**/
@:notNull
@:forward(x, y, z, Set, Copy)
abstract Vector3(BaseVec4) from BaseVec4 to BaseVec4 {
    public inline function new(x: Single, y: Single, z: Single) {
        this = new BaseVec4(x, y, z, 1);
    }

    // CONSTRUCTORS
    public inline static function Zero(): Vector3 {
        return new Vector3(0, 0, 0);
    }

    public inline static function One(): Vector3 {
        return new Vector3(1, 1, 1);
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
    public inline function IndexRead(index: Int): Single {
        if (index == 0) return this.x;
        if (index == 1) return this.y;
        if (index == 2) return this.z;
        throw 'Invalid index when reading Vector3';
    }

    @:op([])
    public inline function IndexWrite(index: Int, value: Single): Void {
        if (index == 0) this.x = value;
        if (index == 1) this.y = value;
        if (index == 2) this.z = value;
        throw 'Invalid index when writing to Vector3';
    }

    // STRING
    @:to
    public inline function ToString(): String {
        return '(${this.x}, ${this.y}, ${this.z})';
    }
}
