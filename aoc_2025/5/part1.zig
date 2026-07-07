const std = @import("std");

pub fn main() void {
    var list: std.ArrayList(u8) = .empty;
    defer list.deinit(std.testing.allocator);

    const file = try std.fs.path.parsePathPosix("~/scratchpad");
    defer file.close();

    std.debug.print("Hello, {s}!\n", .{"world"});
}

// 3-5
// 10-14
// 16-20
// 12-18
//
// 1
// 5
// 8
// 11
// 17
// 32
