import pandas as pd
import matplotlib.pyplot as plt

def readData():
    df = pd.read_csv('ABtester/results.csv')
    return df


df = readData();
successful = df[df['Found'] == True]
unSuccessful = df[df['Found'] == False]

aSuccess = successful[successful['FileName'] == '100780513-2-a.png']
bSuccess = successful[successful['FileName'] == '100780513-2-b.png']

aFail = unSuccessful[unSuccessful['FileName'] == '100780513-2-a.png']
bFail = unSuccessful[unSuccessful['FileName'] == '100780513-2-b.png']

aTimes = aSuccess['Time'].values.tolist()
bTimes = bSuccess['Time'].values.tolist()
print(df)
print('----------------------------')
print(f'Successful Trial for A: {len(aSuccess)} | Successful runs for B: {len(bSuccess)}\nUnsuccessful trials for A: {len(aFail)} | Unsuccessful trials for B: {len(bFail)}')

print('----------------------------')
print(f'A Times: {aTimes} | Average time for A: {(sum(aTimes)/len(aTimes)).__format__(".2f")} milliseconds')
print(f'A Times: {bTimes} | Average time for A: {(sum(bTimes)/len(bTimes)).__format__(".2f")} milliseconds')

print(f'On average, users were able to successfully navigate to the desired spot on page B {((len(bSuccess)/len(df))*100).__format__(".2f")}% of the time vs {((len(aSuccess)/len(df))*100).__format__(".2f")}% of the time for page A')

categories = ['A', 'B']

plt.figure(figsize=(7, 5))
plt.subplot(1, 2, 1)
plt.bar(categories, [len(aSuccess), len(bSuccess)], color=['green', 'darkblue'])
plt.ylabel('Number of Successful Trials')
plt.xlabel('Page Mode')
plt.title('Successful Trials')
plt.subplot(1, 2, 2)
plt.bar(categories, [len(aFail), len(bFail)], color=['darkorange', 'darkred'])
plt.ylabel('Number of Unsuccessful Trials')
plt.xlabel('Page Mode')
plt.title('Unsuccessful Trials')
plt.show()

print(len(successful), len(unSuccessful))