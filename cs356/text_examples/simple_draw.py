import turtle

pen = turtle.Turtle()
pen.up()
pen.pensize(3)

def draw_mountain(position):
    pen.up()
    pen.color("black", "grey")
    #pen.setposition(

def draw_sun():
    pen.up()
    pen.color("black","yellow")
    pen.setposition(-400, 300)
    pen.down()
    pen.begin_fill()
    pen.circle(50)
    pen.end_fill()


def draw_mountains():
    draw_mountain()
    pen.forward(200)
    draw_mountain()
    pen.backward (200)

def draw_trees():
    draw_tree()
    pen.forward(100)
    draw_tree()
    pen.forward(100)
    draw_tree()
    pen.backward(200)

def draw_tree():
    pen.down()
    pen.left(90)
    pen.forward(50)
    pen.right(90)
    pen.forward(50)
    pen.left(45)
    # ...

def draw_landscape():
    #draw_mountains()
    draw_sun()
    #draw_trees()

turtle.bgcolor("lightblue")
draw_landscape()
