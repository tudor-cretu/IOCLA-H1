<h5 align = center> Copyright Cretu Mihnea Tudor 315CAa 2022 - 2023 </h5> 
<h5 align = center> 1st Homework for Programming Languages II Class, Year I - Faculty of Automation Control and Computer Science, Polytechnic University of Bucharest </h5>

<h1 align = center> To pit or not to pit... this is the strategy </h1>
<br>

<h2> 1) Introduction </h2>
<p align = left> This program is designed to analyze sensor data from various systems, specifically tire sensors and power management units (PMUs) in a race car. The program allows the user to input a file containing the sensor data, which is then stored in memory as a set of sensor structs. The user can then interact with the program through a command line interface to analyze and manipulate the data. </p>

<h2> 2) Installation </h2>
<p align = left> To compile the program, simply run the command <i>make</i> in the terminal. This will generate an executable called <i>main</i>. The program requires a binary file containing sensor data to be passed as an argument when running the executable. </p>

<h2> 3) Usage </h2>
<p align = left> Once the program is running, the user will be prompted to enter commands. The available commands are: </p>
<ul>
    <li> print [index]: prints the data for the sensor at the given index.
    <li> analyze [index]: analyzes the data for the sensor at the given index and outputs the results.
    <li> clear: clears the sensors which data is not within the given limits
    <li> exit: exits the program and frees all the memory.
</ul>
<p align = left> The program supports two types of sensors: tire sensors and power management units (PMUs). The print and analyze commands can be used with either type of sensor. </p>

<h2> 4) Program Structure </h2>
<p align = left> The program is divided into three files: </p>
<ul>
    <li> main.c: contains the main function and the command line interface.
    <li> operations.c: contains the functions for analyzing sensor data.
    <li> operations.h: header file for <i>operations.c</i>.
    <li> structs.h: contains the definitions for the sensor structs.
    <li> Makefile: automates the software building procedure 
</ul>