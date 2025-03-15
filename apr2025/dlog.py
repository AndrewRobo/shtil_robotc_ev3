#! python3

#fr = open('D:\shtil_robotc_ev3\\13ir.csv','r')


import csv
 
with open('D:\shtil_robotc_ev3\\13ir.csv', 'r') as csvfile:
    csvreader = csv.reader(csvfile)
    for row in csvreader:
        print(row)



 
	
#import csv
 
data = [['Name', 'Age', 'City'],
        ['Alice', '30', 'New York'],
        ['Bob', '25', 'San Francisco']]
 
with open('output.csv', 'w') as csvfile:
    csvwriter = csv.writer(csvfile)
    for row in data:
        csvwriter.writerow(row)   