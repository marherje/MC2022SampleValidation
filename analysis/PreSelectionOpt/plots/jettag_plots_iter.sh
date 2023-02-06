mkdir testplots/
mkdir testplots/JetTagAnalysis
mkdir testplots/JetTagAnalysis/50
for k in 50 
do
    for cut in {0..7}
    do
	root -l -q JetTag.C\($cut,\"$k\"\)
	mv c_eff_c.png testplots/JetTagAnalysis/50/JetTag_c_Cut${cut}_Kgamma${k}.png
	
	mv c_eff_b.png testplots/JetTagAnalysis/50/JetTag_b_Cut${cut}_Kgamma${k}.png
    done
done
