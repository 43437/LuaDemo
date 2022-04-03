function fun0(x)
    return 0
--    return fun1(x)
end

function fun1(x)
    return debug.traceback()
end

function main(x)
    return fun0(1)
end
