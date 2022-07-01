-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Returns description of crime and mentions bakery as well as three witnesses
SELECT id, description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

--Returns various transcripts WITH KEY INFORMATION:
--Thief withdrew ATM money on Leggett Street
--Theif got into car at bakery parking lot within 10 minutes of the theft
--Theif made a call and said they were taking the earliest flight next morning, asked the other person to purchase the ticket (accomplice)
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;