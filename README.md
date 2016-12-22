# Code Clinics for C++

## Table of Contents
[What Are Code Clinics](#what-are-code-clinics)
[Problem 1: Exploring Lake Pend Orielle]
[Problem 2: Image Analysis]
[Problem 3: Eight Queens]
[Problem 4: Accessing Peripherals]
[Problem 5]: Recursion and Directories
[Problem 6]: Building the Web

### What are Code Clinics?

Code Clinic is a monthly course where a unique problem is introduced to a collection of [Lynda.com]() authors. In response, each author will create a solution using their programming language of choice. You can learn several things from Code Clinic, different approaches to solving a problem, the pros and cons of different languages, and some tips and tricks to incorporate into your own coding practices.

### Problem 1: Exploring Lake Pend Orielle

#### Preface

This month, we'll work on a problem in statistical analysis and, to some extent, handling big data. In this problem, we'll use weather data collected by the U.S. Navy from Lake Pend Oreille in northern Idaho. Lake Pend Oreille is the fifth deepest freshwater lake in the United States, so deep, in fact, that the U.S. Navy uses it to test submarines.

As part of that testing, the U.S. Navy compiles an exhaustive list of weather statistics, wind speed, air temperature, barometric pressure. You can browse this data by pointing your web browser at lpo.dt.navy.mil. You'll find several weather summaries, webcam, and the raw data they collect every five minutes archived as standard text files. For anyone living or working on Lake Pend Oreille, weather statistics are an important part of everyday life. Average wind speed can be very different than median wind speed, especially if you're on a small boat in the middle of the lake.


#### Problem at Hand

In this challenge, each of our authors will use their favorite language to calculate the mean and median of the wind speed, air temperature and barometric pressure recorded at the Deep Moor station for a given date. 

     | Wind Speed | Air Temperature | Barometric Pressure
 --- | --- | --- | ---
 **Mean** | | | 
 **Median** | | |

First, let's briefly review mean and median. These are both statistics.Here we have 14 readings for wind gust at Deep Moor Weather Station on January 1st 2014:
    
    2014_01_01 00:21:24 14
    2014_01_01 00:27:31 14
    2014_01_01 00:33:39 11
    2014_01_01 00:39:47 11
    2014_01_01 00:45:54 11
    2014_01_01 00:52:02 11
    2014_01_01 00:58:09 11
    2014_01_01 01:04:17 3
    2014_01_01 01:10:25 7
    2014_01_01 01:16:32 7
    2014_01_01 01:22:40 7
    2014_01_01 01:28:48 7
    2014_01_01 01:35:55 4
    2014_01_01 01:42:03 8

*You can see the data at [http://lpo.dt.navy.mil/data/DM/2014/2014_01_01/Wind_Gus]()*. 

These is what you can cather from these readings:
	* The first column is the day the wind gust was recorded.
	* The second column is the time it was recorded.
 	* The third column is the wind gust in miles per hour. 
 
 The mean is also known as the average. To collect the mean of a range of numbers, simply add the values in the set, then divide by the number of values. 
 
 In this example, we'll add 14 + 14 + 11 + 11 + 11 + 11 + 11 + 3 + 3 + 3 + 3 + 7 + 7 + 7 + 7 + 4 + 8 = 126. Then we'll divide the sum of 126 by 14 which is the number of values in this set. 

 In this case, the mean is equal to 9.

The median is the number halfway between all the values in a sorted range of values. 

To calculate the median:
	1. Sort the numbers from lowest to highest. 
		* If there's an odd number of values, then just take the middle number. 
		* If there's an even number of values, then calculate the mean of the central two numbers.

In this case, there's an even number of values, so we sort, then we take the average of the middle two values, the 8 and 11, and the median is 9.5.

In addition, some authors have chosen to implement a web service allowing other websites to access the new weather statistics created by the author's program. 

This is typically done by creating a RESTful API, which, when called, returns information in a format known as JSON.

In our case, if I make this HTTP call, I would expect to receive the mean and median for wind speed, air temperature and barometric pressure for the specified date, January 1st, 2014:

     | Wind Speed | Air Temperature | Barometric Pressure
 --- | --- | --- | ---
 **Mean** |6.117 | 38.96 | 29.781
 **Median** | 6.2 | 39.2 | 29.781

and the resulting JSON data looks like this:

    var jsonReturnData = {
         "windSpeed": [{"mean":6.61179039301,"median":6.2}],
         "airTemperature":[{"mean":38.969650655,"median":39.2}],
         "barometricPressure":[{"mean":29.781441048,"median":29.8}]
    }

So, this is our first challenge. Pull statistics from a data set available online. Perhaps you'll want to pause and create a solution of your own. How would you solve the problem? In the next videos, I'll show you how I solve this challenge. 






