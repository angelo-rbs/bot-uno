
# se quiser mudar os bots utilizados altere na primeira linha do laço 

US=0
THEM=0

for i in {1..100};
do
  WINNER=`./uno nossoBot bot_A | grep "nossoBot -" | cut -c 1`
  echo "${i}º jogo"
  
  if [ "$WINNER" -eq 1 ]; 
  then 
    US=$(($US+1)) 
  else 
    THEM=$(($THEM+1))  
  fi
done

echo "ganhamos $US"
echo "perdemos $THEM"