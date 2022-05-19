import requests

bzReal = requests.get("https://api.hypixel.net/skyblock/bazaar")

def getManip(itemName):
  bzRealData = bzReal.json()
  write = open("Repeats.txt", "a")
  read = open("Repeats.txt", "r")
  response = requests.get("https://sky.coflnet.com/api/bazaar/" + itemName + "/history/week")
  foundRepeat = False

  try:
    bzRealData['products'][itemName]
  except:
    print(itemName + " doesn't exist or isn't in the bazaar!")
    return 0
  
  try:
    bzItemData = response.json()
    
    totalBuy = 0
    divideBy = 0
    sellFail = 0
    buyFail = 0
    
    for buy in bzItemData:
      try:
        totalBuy = totalBuy + buy['buy']
        divideBy += 1
      except:
        buyFail += 1

    try:
      average = totalBuy/ divideBy
      if average < 10000:
        return 0
      #Compare
      currentSell = bzRealData['products'][itemName]['sell_summary'][0]['pricePerUnit']
      print("\nAverage buy value of " + itemName + ": " + str("{:.1f}".format(average)) + "\nCurrent buy value of " + itemName + ": " + str("{:.1f}".format(currentSell)))

      #Repeats
      repeatsList = read.readlines()
      for i in repeatsList:
        i  = i.replace("\n", "")
        if str(i) == str(itemName):
          foundRepeat = True
          break

      if foundRepeat == False:
        if (float(currentSell) - float(average) <= float(average) * 0.8 and float(average) > 100000):
          if float(currentSell) - float(average) <= float(average) * 0.5 and float(average) > 100000:
            data = {
              "content" : "<@&976583027935285339>",
              "username" : "BZ Investor"
            }
            data["embeds"] = [
              {
                  "description" : "Average: " + str("{:.1f}".format(average)) + "\nBuy Order: " + str("{:.1f}".format(currentSell)) + "\nInstant Buy: " + str(bzRealData['products'][itemName]['buy_summary'][0]['pricePerUnit']) + "\nProfit Percentage: " + str("{:.1f}".format((((float(average)/float(currentSell))*100)))) + "%",
                  "title" : itemName
              }
            ]
            requests.post('https://discord.com/api/webhooks/976304365130358814/qUFCNIsaOhrq2e4ij3G4Ke_NVWUz3mOUmUtPft7Hr1U-c3s0LgjKYJIBHpav8PUWjz9s', json = data)
          else:
            data = {
              "content" : "<@&976583027935285339>",
              "username" : "BZ Investor"
            }
            data["embeds"] = [
              {
                  "description" : "Average: " + str("{:.1f}".format(average)) + "\nBuy Order: " + str("{:.1f}".format(currentSell)) + "\nInstant Buy: " + str(bzRealData['products'][itemName]['buy_summary'][0]['pricePerUnit']) + "\nProfit Percentage: " + str("{:.1f}".format((((float(average)/float(currentSell))*100)))) + "%",
                  "title" : itemName
              }
            ]
            requests.post('https://discord.com/api/webhooks/976302340007149678/V67JNPhKwmQ59TMeY8eIIaNlLHYQN6PZxcUwxaAAb67LhnIkPKH-byX4TKKVUTDFsWG2', json = data)
          write.write(itemName + "\n")
      #Compare
      data = {
        "username" : "BZ Logger"
      }
      data["embeds"] = [
        {
          "description" : "Average: " + str("{:.1f}".format(average)) + "\nBuy Order: " + str("{:.1f}".format(currentSell)) + "\nInstant Buy: " + str(bzRealData['products'][itemName]['buy_summary'][0]['pricePerUnit']) + "\nProfit Percentage: " + str("{:.1f}".format((((float(average)/float(currentSell))*100)))) + "%",
          "title" : itemName
        }
      ]
      requests.post('https://discord.com/api/webhooks/976582142383521872/qFdxfC_Vxu-YIZ3Rmeq6bNePvy2C4PLEJvCO9NHeXWJx4puk7XBpxZcCGSx62rDHevbf', json = data)
    except:
      print("An error has occurred calculating the average of " + itemName + ". There were " + str(sellFail) + " sell fails and " + str(buyFail) + " buy fails.")
  except:
    print("An error occured grabbing the average of " + itemName + " " + str(response.status_code()))
  write.close()
  read.close()

count = 0
response = requests.get("https://sky.coflnet.com/api/items/bazaar/tags")
bzItems = response.json()
while 1:
  for i in range(len(bzItems)):
    ranTrue = False
    while ranTrue == False:
      try:
        getManip(bzItems[i])
        ranTrue = True
      except:
        print("API call quota reached (100/minute)! Retrying.")
        ranTrue = False
  count += 1
  data = {
    "content" : "<@&976583027935285339>",
    "username" : "BZ Investor"
  }
  data["embeds"] = [
    {
        "description" : "Repeats: " + str(count),
        "title" : "Repeat Count"
    }
  ]
  requests.post("https://discord.com/api/webhooks/976582142383521872/qFdxfC_Vxu-YIZ3Rmeq6bNePvy2C4PLEJvCO9NHeXWJx4puk7XBpxZcCGSx62rDHevbf", json = data)
  if count % 5 == 0:
    d = open("Repeats.txt", "w")
    d.close()
    count = 0
