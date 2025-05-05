# Tourism-Management-System
## Description
The Tourist Reservation System is a C++ console-based application designed to simulate a simple travel booking platform with functionalities for both admins and users. It allows users to explore available tourist destinations, make bookings, and view their reservations. Admins can manage trip listings, view bookings, and maintain the overall database. This project makes use of basic file handling, user authentication, and menu-driven navigation to emulate a real-world reservation environment.
##  Features
### User Side:
Sign Up / Login

View Available Trips

Book a Trip (by destination code)

View Your Booking Status
### Admin Side:
Admin Login (hardcoded credentials)

Add New Trips

View All Trip Listings

View All User Bookings
## Technologies Used
Language: C++

Paradigm: Procedural and Object-Oriented Programming

File Handling: Plain text files for data storage (trip.txt, user.txt)

Environment: Any C++ compiler (e.g., GCC, Turbo C++, Code::Blocks)
## Data Storage
User bookings are stored in user.txt

Trip details are stored in trip.txt

Each record is serialized as a pipe-separated string (e.g., Name|Phone|People|TripCode|Date|Status|)
## Admin Credentials
Username: Parth
Password: 1414

## How to Run
### 1.Clone the repository:
    git clone https://github.com/yourusername/tourist-reservation-system.git
    cd tourist-reservation-system
### 2.Compile the program:
    g++ -o tourist tourist.cpp
### 3.Run the executable:
    ./tourist
    
On Windows, use tourist.exe instead of ./tourist.
