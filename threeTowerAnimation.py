import turtle

turtle.bgcolor("lightblue")
turtle.speed(3)

def draw_pole(x, y):
    turtle.penup()
    turtle.goto(x, y)
    turtle.pendown()
    turtle.setheading(90)
    turtle.forward(180)

def draw_disc(x, y, len):
    turtle.penup()
    turtle.goto(x, y)
    turtle.pendown()
    turtle.setheading(0)
    turtle.forward(len)

turtle.color("black")
turtle.pensize(9)

draw_pole(-120, -120)
draw_pole(0, -120)
draw_pole(120, -120)

turtle.delay(80)
turtle.pensize(30)

turtle.color("green")
draw_disc(-165, -120, 90)

turtle.color("yellow")
draw_disc(-150, -80, 60)

turtle.color("blue")
draw_disc(-135, -40, 30)

turtle.hideturtle()
turtle.done()
