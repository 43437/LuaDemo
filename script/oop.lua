Shape = {area = 0}
-- 基础类方法 new
function Shape:new (o,side)
  o = o or {}
  setmetatable(o, {__index = self})
  side = side or 0
  self.area = side*side;
  return o
end

-- 基础类方法 printArea
function Shape:printArea ()
  output("面积为 ",self.area)
end

Square = Shape:new()
-- 派生类方法 new
function Square:new (o,side)
  o = o or Shape:new(o,side)
  setmetatable(o, {__index = self})
  return o
end

-- 派生类方法 printArea
function Square:printArea ()
  output("正方形面积为 ",self.area)
end

Rectangle = Shape:new()
-- 派生类方法 new
function Rectangle:new (o,length,breadth)
  o = o or Shape:new(o)
  setmetatable(o, {__index = self})
  self.area = length * breadth
  return o
end

-- 派生类方法 printArea
function Rectangle:printArea ()
  output("矩形面积为 ", self.area)
end

msg = '> '
function output(...)
    local arg={...}    --> arg 为一个表，局部变量
    msg = string.format("%s\n%s", msg, table.concat(arg))
end

function main()

    -- 创建对象
    myshape = Shape:new(nil,10)
    myshape:printArea()

    -- 创建对象
    mysquare = Square:new(nil,10)
    mysquare:printArea()

    myrectangle = Rectangle:new(nil,10,20)
    myrectangle:printArea()

    return msg
end
