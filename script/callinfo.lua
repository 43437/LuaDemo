function func0(x, y, z)
    callinfo.callback1(x+y, z)
    return x, y
end

function main(x, y)
    callinfo.callback0(x+1, y+1)
end
