-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Returns description of crime and mentions bakery as well as three witnesses
SELECT id, description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10;