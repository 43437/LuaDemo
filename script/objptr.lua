function process(x, y)
    return x + y
end

function main(x, y)
    z = process(x, y)
    c_obj.callback(z)
end
