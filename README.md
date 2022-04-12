# COVID-VACCINATION-SLOT-ALLOCATION
This project is based on allotting Covishield vaccination slots for registered people. It creates a vaccination queue based on the following criteria:
•	First dose vaccination status
•	Domain of work  (health care workers/ front line and govt. workers/others)
•	Age  (60 years and above/45 years and above /18 years and above)
•	Health conditions  (Underlying health issues eg: diabetes ,cancer ,heart conditions etc./no underlying health issues)

The people who have registered for the vaccine are divided into the following categories :
Category-1       Health care, Front Line and government workers
Category-2       People whose second dose has become due, people aged 60 and above
Category-3       People with underlying health conditions, people aged 45 years and above 
Non-Priority     People who do not come under any of the above categories

A priority queue is a special type of queue in which each element is associated with a priority value. Here, people are provided slots for vaccination based on the categories they belong to, the highest priority being given to category 1 followed by the categories 2,3 and non-priority. That is people who fall into the higher priority categories are served first. However, if we encounter people with the same priority, then they are served according to their order in the queue
