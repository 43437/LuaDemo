local tb = {name="hwang", age=1}
function tb:f_name()
    return tb.name
end

function main(greet)
    gy.log('simple lua function ', 'main', tb)
    return greet .. ' lua !!!'
end
