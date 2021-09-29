# Simple Snake Game in Python 3 for Beginners
# By @TokyoEdTech

import turtle
import time
import random
import serial
from serial import Serial

delay = 0.1

# Serial Connection setup
ser = serial.Serial('COM3', baudrate = 9600, timeout = 1)
time.sleep(3)
dataPoints = 3
dataList = [0]*dataPoints

direct = "forward"

def getValues():
    ser.write(b'g')
    arduinoData = ser.readline().decode('ascii').split('\r\n')

    return arduinoData


# Score
score = 0
high_score = 0

# Set up the screen
wn = turtle.Screen()
wn.title("Snake Game by @TokyoEdTech")
wn.bgcolor("green")
wn.setup(width=600, height=600)
wn.tracer(0)  # Turns off the screen updates

# Snake head
head = turtle.Turtle()
head.speed(0)
head.shape("square")
head.color("black")
head.penup()
head.goto(0, 0)
head.direction = "stop"

# Snake food
food = turtle.Turtle()
food.speed(0)
food.shape("circle")
food.color("red")
food.penup()
food.goto(0, 100)

segments = []

# Pen
pen = turtle.Turtle()
pen.speed(0)
pen.shape("square")
pen.color("white")
pen.penup()
pen.hideturtle()
pen.goto(0, 260)
pen.write("Score: 0  High Score: 0", align="center", font=("Courier", 24, "normal"))


# Functions
def go_up():
    if head.direction != "down":
        head.direction = "up"


def go_down():
    if head.direction != "up":
        head.direction = "down"


def go_left():
    if head.direction != "right":
        head.direction = "left"


def go_right():
    if head.direction != "left":
        head.direction = "right"


def move():
    if direct == "up":
        y = head.ycor()
        head.sety(y + 20)

    if direct == "down":
        y = head.ycor()
        head.sety(y - 20)

    if direct == "left":
        x = head.xcor()
        head.setx(x - 20)

    if direct == "right":
        x = head.xcor()
        head.setx(x + 20)


# Keyboard bindings
wn.listen()
wn.onkey(go_up, "w")
wn.onkey(go_down, "s")
wn.onkey(go_left, "a")
wn.onkey(go_right, "d")

# Main game loop

counter = 0
while True:
    wn.update()

    # Get Arduino data
    for i in range(0, dataPoints):
        data = getValues()
        del data[-1] #deletes empty string
        data = data[0] #makes data a string


    first = data.find('+++', 0) #Finds instance of first +++
    second = data.find('+++', (first + 1)) #Finds second instance of +++


    ### Pitch is the x axis rotation, Roll is the y axis rotation
    pitch = data[:first] #string before first +++
    roll = data[(first + 3):second] #string before second +++ and after first +++

    pitch = float(pitch)
    roll = float(roll)

    print("Pitch is:", pitch, "Roll is:", roll)
    ### How to figure out if a x or y axis rotation is being done

    if counter == 0:
        default_p = pitch #first value of pitch
        default_r = roll #first value of roll
    counter += 1

    if abs(pitch - default_p) > abs(roll - default_r):
        if pitch > 0:
            direct = "up"
            print(direct)
        if pitch < 0:
            direct = "down"
            print(direct)

    if abs(pitch - default_p) < abs(roll - default_r):
        if roll > 0:
            direct = "left"
            print(direct)
        elif pitch < 0:
            direct = "right"
            print(direct)

    # Check for a collision with the border
    if head.xcor() > 290 or head.xcor() < -290 or head.ycor() > 290 or head.ycor() < -290:
        time.sleep(1)
        head.goto(0, 0)
        head.direction = "stop"

        # Hide the segments
        for segment in segments:
            segment.goto(1000, 1000)

        # Clear the segments list
        segments.clear()

        # Reset the score
        score = 0

        # Reset the delay
        delay = 0.1

        pen.clear()
        pen.write("Score: {}  High Score: {}".format(score, high_score), align="center", font=("Courier", 24, "normal"))

        # Check for a collision with the food
    if head.distance(food) < 20:
        # Move the food to a random spot
        x = random.randint(-290, 290)
        y = random.randint(-290, 290)
        food.goto(x, y)

        # Add a segment
        new_segment = turtle.Turtle()
        new_segment.speed(0)
        new_segment.shape("square")
        new_segment.color("grey")
        new_segment.penup()
        segments.append(new_segment)

        # Shorten the delay
        delay -= 0.001

        # Increase the score
        score += 10

        if score > high_score:
            high_score = score

        pen.clear()
        pen.write("Score: {}  High Score: {}".format(score, high_score), align="center", font=("Courier", 24, "normal"))

        # Move the end segments first in reverse order
    for index in range(len(segments) - 1, 0, -1):
        x = segments[index - 1].xcor()
        y = segments[index - 1].ycor()
        segments[index].goto(x, y)

    # Move segment 0 to where the head is
    if len(segments) > 0:
        x = head.xcor()
        y = head.ycor()
        segments[0].goto(x, y)

    move()

    # Check for head collision with the body segments
    for segment in segments:
        if segment.distance(head) < 20:
            time.sleep(1)
            head.goto(0, 0)
            head.direction = "stop"

            # Hide the segments
            for segment in segments:
                segment.goto(1000, 1000)

            # Clear the segments list
            segments.clear()

            # Reset the score
            score = 0

            # Reset the delay
            delay = 0.1

            # Update the score display
            pen.clear()
            pen.write("Score: {}  High Score: {}".format(score, high_score), align="center",
                      font=("Courier", 24, "normal"))

    time.sleep(delay)

wn.mainloop()