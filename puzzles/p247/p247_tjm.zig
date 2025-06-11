const std = @import("std");

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();

    var prng = std.Random.DefaultPrng.init(2);
    const random = prng.random();
    // each player card is fixed and non overlapping
    const h1 = [_]u8{ 0, 1, 2, 3, 4, 5, 6, 7, 8,};
    const h2 = [_]u8{ 10, 11, 12, 13, 14, 15, 16, 17, 18,};


    // our deck of 72 tiles 
    var data = [_]u8{
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
                     10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
                     20, 21, 22, 23,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
                     10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
                     20, 21, 22, 23,
                     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
                     10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
                     20, 21, 22, 23,
                    };
    const deck = data[0..]; // Get a slice from the array
    try stdout.print("original deck : {any}\n", .{deck});
    random.shuffle(u8,deck);
    try stdout.print("shuffled deck : {any}\n", .{deck});

    // matrix to store the j
    var wmatrix: [10][10] i32 = [_][10]i32{[_]i32{0} ** 10} ** 10;
    var lmatrix: [10][10] i32 = [_][10]i32{[_]i32{0} ** 10} ** 10;
    for (0..40000) |_| {
        var t1matrix: [10][10] i32 = [_][10]i32{[_]i32{0} ** 10} ** 10;
        random.shuffle(u8,deck);
        var h1f = [_]u8{ 0, 0, 0, 0, 0, 0, 0, 0, 0,};
        var h2f = [_]u8{ 0, 0, 0, 0, 0, 0, 0, 0, 0,};

        var idx:u8 = 0;
//        try stdout.print(" deck is:  {any} \n", .{deck});
        
        for (deck) |card| {
            var h1done : bool = true;
            var h2done : bool = true;
            idx +=1;
            var h1cnt : u8 = 0;
            var h2cnt : u8 = 0;
            for (h1,h2,&h1f,&h2f) |v1,v2,*r1,*r2|{
                if (v1 == card){
                    r1.* = 1;
                }
                if (r1.* != 1){
                    h1done = false;
                }
                if (v2 == card){
                    r2.* = 1;
                }
                if (r2.* != 1){
                    h2done = false;
                }
                h1cnt += r1.*;
                h2cnt += r2.*;
            }

            t1matrix[h1cnt][h2cnt] = 1;

            if(h1done and h2done){
                break;
            }
            if(h1done){
                var i: usize = 0;
                while (i < 10) : (i += 1) {
                    var j: usize = 0;
                    while (j < 10) : (j += 1) {
                        wmatrix[i][j] += t1matrix[i][j];
                    }
                }
                break;
            }
            if(h2done){
                var i: usize = 0;
                while (i < 10) : (i += 1) {
                    var j: usize = 0;
                    while (j < 10) : (j += 1) {
                        lmatrix[i][j] += t1matrix[i][j];
                    }
                }
                break;
            }


        }
    }
    var i: usize = 0;
    while (i < wmatrix.len) : (i += 1) {
        var j: usize = 0;
        while (j < wmatrix[i].len) : (j += 1) {
            const wf: f64 = @as(f64,@floatFromInt(wmatrix[i][j]));
            const lf: f64 = @as(f64,@floatFromInt(lmatrix[i][j]));
            try stdout.print("{d:.5} ", .{wf/(lf+wf)});
        }
        try stdout.print("\n", .{});
    }
}
