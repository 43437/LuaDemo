function main(x, y, op)
    z = 0
    if ('add' == op)
    then
        z = simple_func.add(x, y)
    else
        z = simple_func.sub(x, y)
    end
    return z, string.format("%d %s %d is", x, op, y)
end
