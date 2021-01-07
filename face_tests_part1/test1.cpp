

/**************************************************************************
234124 - Introduction To Systems Programming
Spring 2019
HW3 - C++

In charge : Israel Gutter
            Noy Naor
For questions and clarifications : Please use the forum in Moodle.
**************************************************************************/

#include <iostream>
#include <string.h>
using std::string;
#include "eurovision.h"

using std::cout;
using std::endl;



void TEST1(){
    freopen ("results/test1myresult.txt","w",stdout);
    MainControl eurovision;
    Participant p1("georgia","song_georgia",126,"singer_georgia");
    cout<<p1<<endl;
    Participant p2("bosnia","song_bosnia",102,"singer_bosnia");
    cout<<p2<<endl;
    Participant p3("andora","song_andora",201,"singer_andora");
    cout<<p3<<endl;
    Participant p4("estonia","song_estonia",172,"singer_estonia");
    cout<<p4<<endl;
    Participant p5("belgium","song_belgium",102,"singer_belgium");
    cout<<p5<<endl;
    Participant p6("malta","song_malta",153,"singer_malta");
    cout<<p6<<endl;
    Participant p7("uk","song_uk",121,"singer_uk");
    cout<<p7<<endl;
    Participant p8("bulgaria","song_bulgaria",100,"singer_bulgaria");
    cout<<p8<<endl;
    Participant p9("france","song_france",186,"singer_france");
    cout<<p9<<endl;
    Participant p10("slovakia","song_slovakia",192,"singer_slovakia");
    cout<<p10<<endl;
    Participant p11("israel","song_israel",166,"singer_israel");
    cout<<p11<<endl;
    Participant p12("israel","song_israel",138,"singer_israel");
    cout<<p12<<endl;
    Participant p13("cyrpus","song_cyrpus",203,"singer_cyrpus");
    cout<<p13<<endl;
    Participant p14("bulgaria","song_bulgaria",145,"singer_bulgaria");
    cout<<p14<<endl;
    Participant p15("russia","song_russia",189,"singer_russia");
    cout<<p15<<endl;
    Participant p16("slovenia","song_slovenia",154,"singer_slovenia");
    cout<<p16<<endl;
    Participant p17("armenia","song_armenia",211,"singer_armenia");
    cout<<p17<<endl;
    Participant p18("russia","song_russia",176,"singer_russia");
    cout<<p18<<endl;
    Participant p19("hungary","song_hungary",101,"singer_hungary");
    cout<<p19<<endl;
    Participant p20("switzerland","song_switzerland",218,"singer_switzerland");
    cout<<p20<<endl;
    Participant p21("hungary","song_hungary",122,"singer_hungary");
    cout<<p21<<endl;
    Participant p22("estonia","song_estonia",155,"singer_estonia");
    cout<<p22<<endl;
    Participant p23("croatia","song_croatia",132,"singer_croatia");
    cout<<p23<<endl;
    Participant p24("croatia","song_croatia",112,"singer_croatia");
    cout<<p24<<endl;
    Participant p25("estonia","song_estonia",107,"singer_estonia");
    cout<<p25<<endl;
    Participant p26("greece","song_greece",183,"singer_greece");
    cout<<p26<<endl;
    Participant p27("andora","song_andora",117,"singer_andora");
    cout<<p27<<endl;
    Participant p28("slovakia","song_slovakia",162,"singer_slovakia");
    cout<<p28<<endl;
    Participant p29("russia","song_russia",215,"singer_russia");
    cout<<p29<<endl;
    Participant p30("belgium","song_belgium",179,"singer_belgium");
    cout<<p30<<endl;
    Participant p31("bosnia","song_bosnia",177,"singer_bosnia");
    cout<<p31<<endl;
    Participant p32("serbia","song_serbia",225,"singer_serbia");
    cout<<p32<<endl;
    Participant p33("georgia","song_georgia",200,"singer_georgia");
    cout<<p33<<endl;
    Participant p34("belgium","song_belgium",177,"singer_belgium");
    cout<<p34<<endl;
    Participant p35("moldova","song_moldova",176,"singer_moldova");
    cout<<p35<<endl;
    Participant p36("russia","song_russia",174,"singer_russia");
    cout<<p36<<endl;
    p16.update("new_song",0,"");
    p15.update("new_song",0,"");
    p7.update("new_song",0,"");
    p8.update("new_song",0,"");
    p12.update("new_song",0,"newsinger");
    p14.update("new_song",0,"newsinger");
    p23.update("new_song",0,"newsinger");
    p34.update("new_song",0,"newsinger");
    p17.update("new_song",185,"newsinger");
    p17.update("new_song",133,"newsinger");
    p35.update("new_song",127,"newsinger");
    p20.update("new_song",129,"newsinger");
    cout<<eurovision<<endl;
    eurovision+=p27;
    eurovision+=p8;
    eurovision+=p24;
    eurovision+=p18;
    eurovision+=p9;
    eurovision+=p26;
    eurovision+=p20;
    eurovision+=p27;
    eurovision+=p22;
    eurovision+=p11;
    eurovision+=p31;
    eurovision+=p32;
    eurovision+=p36;
    eurovision+=p26;
    cout<<eurovision<<endl;
    eurovision-=p16;
    eurovision-=p13;
    eurovision-=p33;
    eurovision-=p20;
    eurovision-=p1;
    eurovision+=p14;
    eurovision+=p24;
    eurovision+=p28;
    eurovision-=p5;
    eurovision+=p14;
    eurovision-=p33;
    eurovision+=p26;
    eurovision+=p4;
    eurovision+=p26;
    eurovision-=p1;
    eurovision-=p8;
    eurovision-=p13;
    eurovision+=p14;
    eurovision+=p8;
    eurovision-=p19;
    eurovision+=p22;
    eurovision-=p7;
    eurovision-=p32;
    eurovision-=p33;
    cout<<eurovision<<endl;
    eurovision.setPhase(Contest);
    eurovision.setPhase(Voting);
    std::cout<<eurovision.participate("bulgaria")<<std::endl;
    std::cout<<eurovision.participate("lithiania")<<std::endl;
    std::cout<<eurovision.participate("belgium")<<std::endl;
    std::cout<<eurovision.participate("france")<<std::endl;
    std::cout<<eurovision.participate("norway")<<std::endl;
    std::cout<<eurovision.participate("greece")<<std::endl;
    std::cout<<eurovision.participate("lithiania")<<std::endl;
    std::cout<<eurovision.participate("netherlands")<<std::endl;
    std::cout<<eurovision.participate("spain")<<std::endl;
    std::cout<<eurovision.participate("netherlands")<<std::endl;
    std::cout<<eurovision.participate("uk")<<std::endl;
    std::cout<<eurovision.participate("belarus")<<std::endl;
    std::cout<<eurovision.participate("moldova")<<std::endl;
    std::cout<<eurovision.participate("austria")<<std::endl;
    p26.update("",120,"");
    cout<<p26<<endl;
    p29.update("",120,"");
    cout<<p29<<endl;
    p9.update("",120,"");
    cout<<p9<<endl;
    p16.update("",120,"");
    cout<<p16<<endl;
    p9.update("",120,"");
    cout<<p9<<endl;
    p10.update("",120,"");
    cout<<p10<<endl;
    p16.update("",120,"");
    cout<<p16<<endl;
    p28.update("",120,"");
    cout<<p28<<endl;
    p31.update("",120,"");
    cout<<p31<<endl;
    p25.update("",120,"");
    cout<<p25<<endl;
    p3.update("",120,"");
    cout<<p3<<endl;
    p24.update("",120,"");
    cout<<p24<<endl;
    p2.update("",120,"");
    cout<<p2<<endl;
    p3.update("",120,"");
    cout<<p3<<endl;
    Voter v1("armenia",Regular);
    Voter v2("luxembourg",Regular);
    Voter v3("hungary",Regular);
    Voter v4("russia");
    Voter v5("norway");
    Voter v6("france",Regular);
    Voter v7("italy",Regular);
    Voter v8("ukraine",Judge);
    Voter v9("israel",Judge);
    Voter v10("turkey");
    Voter v11("sweden",Regular);
    Voter v12("france",Judge);
    Voter v13("russia",Regular);
    Voter v14("turkey",Regular);
    Voter v15("luxembourg",Regular);
    Voter v16("andora",Regular);
    Voter v17("turkey",Regular);
    Voter v18("sweden",Judge);
    Voter v19("bulgaria");
    Voter v20("ukraine");
    Voter v21("belgium",Regular);
    Voter v22("croatia",Judge);
    Voter v23("austria");
    Voter v24("turkey");
    Voter v25("croatia");
    Voter v26("russia",Regular);
    Voter v27("norway");
    Voter v28("estonia",Regular);
    Voter v29("latvia",Judge);
    Voter v30("estonia",Judge);
    Voter v31("norway",Judge);
    Voter v32("germany");
    Voter v33("armenia");
    Voter v34("austria");
    Voter v35("lithiania",Judge);
    Voter v36("italy",Judge);
    Voter v37("bulgaria",Regular);
    Voter v38("ireland",Judge);
    Voter v39("georgia");
    Voter v40("spain",Judge);
    Voter v41("turkey",Regular);
    Voter v42("estonia");
    Voter v43("andora",Judge);
    Voter v44("norway");
    Voter v45("georgia");
    Voter v46("belarus",Judge);
    Voter v47("luxembourg",Judge);
    Voter v48("bosnia",Regular);
    Voter v49("belarus",Judge);
    Voter v50("croatia",Judge);
    Voter v51("russia",Judge);
    Voter v52("russia");
    Voter v53("turkey",Regular);
    Voter v54("ukraine",Judge);
    Voter v55("croatia",Regular);
    Voter v56("netherlands",Judge);
    Voter v57("hungary");
    Voter v58("austria");
    Voter v59("croatia",Judge);
    Voter v60("bulgaria",Judge);
    Voter v61("belarus");
    Voter v62("latvia",Judge);
    Voter v63("cyrpus",Regular);
    Voter v64("cyrpus",Regular);
    Voter v65("georgia",Regular);
    Voter v66("russia",Judge);
    Voter v67("andora",Regular);
    Voter v68("italy",Regular);
    Voter v69("spain");
    Voter v70("israel",Judge);
    Voter v71("bulgaria");
    Voter v72("germany",Judge);
    Voter v73("andora",Regular);
    Voter v74("malta",Judge);
    Voter v75("ireland");
    Voter v76("switzerland",Regular);
    Voter v77("belgium",Judge);
    Voter v78("france",Regular);
    Voter v79("belarus",Regular);
    Voter v80("turkey");
    Voter v81("greece",Judge);
    Voter v82("luxembourg",Judge);
    Voter v83("israel");
    Voter v84("italy",Judge);
    Voter v85("estonia",Judge);
    Voter v86("georgia",Regular);
    Voter v87("estonia");
    Voter v88("sweden",Regular);
    Voter v89("andora",Regular);
    Voter v90("uk");
    Voter v91("belgium");
    Voter v92("italy",Regular);
    Voter v93("latvia",Judge);
    Voter v94("slovakia",Regular);
    Voter v95("switzerland",Judge);
    Voter v96("netherlands");
    Voter v97("norway",Judge);
    Voter v98("cyrpus",Judge);
    Voter v99("cyrpus",Regular);
    cout<<eurovision<<endl;
    eurovision+=Vote(v71,"bosnia");
    eurovision+=Vote(v98,"croatia","kazakhastan","slovakia");
    eurovision+=Vote(v61,"kazakhastan");
    eurovision+=Vote(v16,"russia");
    eurovision+=Vote(v41,"russia");
    eurovision+=Vote(v60,"norway","austria","italy","kazakhastan","estonia");
    eurovision+=Vote(v61,"belgium");
    eurovision+=Vote(v12,"slovakia","greece","estonia","kazakhastan","turkey","cyrpus");
    eurovision+=Vote(v1,"russia");
    eurovision+=Vote(v35,"turkey","bosnia");
    eurovision+=Vote(v33,"croatia");
    eurovision+=Vote(v24,"latvia");
    eurovision+=Vote(v38,"kazakhastan","malta","france","bulgaria","georgia","italy","serbia","norway","bosnia");
    eurovision+=Vote(v71,"latvia");
    eurovision+=Vote(v61,"ukraine");
    eurovision+=Vote(v22,"georgia","sweden","croatia","switzerland","germany","spain","armenia");
    eurovision+=Vote(v41,"estonia");
    eurovision+=Vote(v92,"andora");
    eurovision+=Vote(v13,"ireland");
    eurovision+=Vote(v24,"israel");
    eurovision+=Vote(v6,"switzerland");
    eurovision+=Vote(v7,"russia");
    eurovision+=Vote(v86,"armenia");
    eurovision+=Vote(v72,"norway","armenia","lithiania","moldova","russia","germany","latvia");
    eurovision+=Vote(v30,"luxembourg","italy","ukraine","spain","belgium");
    eurovision+=Vote(v64,"moldova");
    eurovision+=Vote(v63,"belarus");
    eurovision+=Vote(v98,"russia","croatia");
    eurovision+=Vote(v98,"austria","armenia","luxembourg");
    eurovision+=Vote(v35,"russia","spain","netherlands");
    eurovision+=Vote(v67,"armenia");
    eurovision+=Vote(v96,"france");
    eurovision+=Vote(v32,"andora");
    eurovision+=Vote(v86,"cyrpus");
    eurovision+=Vote(v31,"france","malta","armenia");
    eurovision+=Vote(v31,"greece","latvia","norway","belarus","armenia");
    eurovision+=Vote(v99,"serbia");
    eurovision+=Vote(v64,"cyrpus");
    eurovision+=Vote(v18,"sweden","israel","kazakhastan","moldova","serbia","ukraine","turkey","spain");
    eurovision+=Vote(v89,"norway");
    eurovision+=Vote(v32,"armenia");
    eurovision+=Vote(v1,"serbia");
    eurovision+=Vote(v31,"andora","greece","slovakia","switzerland","cyrpus","armenia","kazakhastan","bosnia");
    eurovision+=Vote(v91,"russia");
    eurovision+=Vote(v41,"greece");
    eurovision+=Vote(v4,"slovenia");
    eurovision+=Vote(v46,"belarus","armenia","serbia","austria","moldova","belarus","sweden","bosnia","italy");
    eurovision+=Vote(v68,"bosnia");
    eurovision+=Vote(v41,"latvia");
    eurovision+=Vote(v15,"malta");
    eurovision+=Vote(v47,"ukraine","france","sweden","norway");
    eurovision+=Vote(v29,"bosnia","netherlands","andora","moldova","belarus","kazakhastan","slovakia","croatia","bosnia","spain");
    eurovision+=Vote(v37,"hungary");
    eurovision+=Vote(v96,"lithiania");
    eurovision+=Vote(v14,"israel");
    eurovision+=Vote(v24,"latvia");
    eurovision+=Vote(v12,"ireland","belgium","slovakia","switzerland","estonia","hungary");
    eurovision+=Vote(v22,"latvia","armenia","lithiania","andora","netherlands","belarus","norway","bulgaria");
    eurovision+=Vote(v61,"bosnia");
    eurovision+=Vote(v60,"hungary","luxembourg","slovakia","israel","bulgaria","latvia");
    eurovision+=Vote(v55,"slovenia");
    eurovision+=Vote(v70,"ireland","netherlands");
    eurovision+=Vote(v39,"spain");
    eurovision+=Vote(v29,"bulgaria","armenia","netherlands","georgia","greece","belgium");
    eurovision+=Vote(v99,"slovenia");
    eurovision+=Vote(v36,"spain","croatia","andora","netherlands");
    eurovision+=Vote(v88,"latvia");
    eurovision+=Vote(v58,"slovenia");
    eurovision+=Vote(v96,"lithiania");
    eurovision+=Vote(v25,"hungary");
    eurovision+=Vote(v78,"ukraine");
    eurovision+=Vote(v35,"slovakia","russia","bosnia","germany","croatia");
    eurovision+=Vote(v19,"latvia");
    eurovision+=Vote(v92,"greece");
    eurovision+=Vote(v47,"belarus","lithiania","slovenia","bulgaria","latvia","bosnia");
    eurovision+=Vote(v98,"lithiania","greece","malta","armenia");
    eurovision+=Vote(v77,"norway","hungary","armenia");
    eurovision+=Vote(v76,"spain");
    eurovision+=Vote(v8,"armenia","croatia","italy","armenia");
    eurovision+=Vote(v36,"spain","russia","belarus","hungary","estonia","italy","netherlands","malta");
    eurovision+=Vote(v71,"andora");
    eurovision+=Vote(v97,"armenia","france","israel","serbia");
    eurovision+=Vote(v40,"belarus","spain","france","russia","kazakhastan","armenia");
    eurovision+=Vote(v45,"ireland");
    eurovision+=Vote(v78,"spain");
    eurovision+=Vote(v17,"malta");
    eurovision+=Vote(v4,"georgia");
    eurovision+=Vote(v48,"greece");
    eurovision+=Vote(v41,"lithiania");
    eurovision+=Vote(v31,"sweden","estonia","switzerland","cyrpus","bosnia","slovenia");
    eurovision+=Vote(v22,"israel","hungary","israel","spain","kazakhastan");
    eurovision+=Vote(v26,"italy");
    eurovision+=Vote(v25,"hungary");
    eurovision+=Vote(v48,"latvia");
    eurovision+=Vote(v29,"slovenia","kazakhastan","sweden","armenia","andora");
    eurovision+=Vote(v82,"armenia","luxembourg");
    eurovision+=Vote(v20,"turkey");
    eurovision+=Vote(v31,"belarus","moldova","belgium","bulgaria","cyrpus");
    eurovision+=Vote(v79,"hungary");
    eurovision+=Vote(v53,"bulgaria");
    eurovision+=Vote(v4,"spain");
    eurovision+=Vote(v84,"moldova","greece","ireland","lithiania","georgia","bulgaria","russia");
    eurovision+=Vote(v16,"france");
    eurovision+=Vote(v82,"russia","cyrpus","netherlands","sweden");
    eurovision+=Vote(v7,"luxembourg");
    eurovision+=Vote(v8,"norway","latvia","bosnia","norway","belarus","malta","moldova","greece","slovakia");
    eurovision+=Vote(v72,"lithiania","moldova","russia","kazakhastan","ukraine","greece");
    eurovision+=Vote(v37,"malta");
    eurovision+=Vote(v80,"norway");
    eurovision+=Vote(v74,"luxembourg","sweden","bosnia","kazakhastan","switzerland");
    eurovision+=Vote(v62,"slovakia","austria","germany","france");
    eurovision+=Vote(v48,"kazakhastan");
    eurovision+=Vote(v49,"norway","bosnia","moldova","latvia","cyrpus","kazakhastan","belgium","switzerland");
    eurovision+=Vote(v58,"latvia");
    eurovision+=Vote(v26,"armenia");
    eurovision+=Vote(v95,"greece","slovakia","cyrpus","greece","israel","austria","italy","armenia","belgium");
    eurovision+=Vote(v84,"ireland","italy","bosnia","bulgaria","croatia","switzerland","hungary");
    eurovision+=Vote(v12,"croatia","malta","moldova","russia","slovakia","belarus");
    eurovision+=Vote(v6,"austria");
    eurovision+=Vote(v51,"france","hungary","sweden","greece","andora","russia","italy","estonia","latvia");
    eurovision+=Vote(v57,"ukraine");
    eurovision+=Vote(v68,"turkey");
    eurovision+=Vote(v39,"georgia");
    eurovision+=Vote(v24,"serbia");
    eurovision+=Vote(v27,"georgia");
    eurovision+=Vote(v78,"luxembourg");
    eurovision+=Vote(v66,"israel","slovakia");
    eurovision+=Vote(v54,"serbia","cyrpus","belarus","spain","austria","slovakia","andora");
    eurovision+=Vote(v49,"georgia","russia","italy","moldova","norway","armenia","belarus","slovakia");
    eurovision+=Vote(v78,"turkey");
    eurovision+=Vote(v24,"ukraine");
    eurovision+=Vote(v32,"cyrpus");
    eurovision+=Vote(v29,"lithiania","georgia","bulgaria","hungary","turkey");
    eurovision+=Vote(v57,"cyrpus");
    eurovision+=Vote(v11,"russia");
    eurovision+=Vote(v5,"luxembourg");
    eurovision+=Vote(v64,"switzerland");
    eurovision+=Vote(v16,"bosnia");
    eurovision+=Vote(v3,"belgium");
    eurovision+=Vote(v73,"switzerland");
    eurovision+=Vote(v92,"switzerland");
    eurovision+=Vote(v93,"germany","latvia","malta","turkey","netherlands");
    eurovision+=Vote(v60,"malta","bulgaria","switzerland");
    eurovision+=Vote(v45,"croatia");
    eurovision+=Vote(v33,"armenia");
    eurovision+=Vote(v49,"georgia","norway","germany","austria","cyrpus","bosnia");
    eurovision+=Vote(v47,"malta","turkey","slovakia","austria","latvia","kazakhastan","greece");
    eurovision+=Vote(v89,"moldova");
    eurovision+=Vote(v73,"cyrpus");
    eurovision+=Vote(v41,"serbia");
    eurovision+=Vote(v41,"lithiania");
    eurovision+=Vote(v29,"malta","luxembourg","spain","netherlands","germany");
    eurovision+=Vote(v67,"hungary");
    eurovision+=Vote(v11,"latvia");
    eurovision+=Vote(v92,"luxembourg");
    eurovision+=Vote(v67,"italy");
    eurovision+=Vote(v45,"hungary");
    eurovision+=Vote(v1,"estonia");
    eurovision+=Vote(v71,"georgia");
    eurovision+=Vote(v25,"georgia");
    eurovision+=Vote(v24,"luxembourg");
    eurovision+=Vote(v66,"austria","ukraine","bulgaria","spain","sweden","georgia");
    eurovision+=Vote(v25,"slovenia");
    eurovision+=Vote(v76,"slovenia");
    eurovision+=Vote(v35,"sweden","bulgaria");
    eurovision+=Vote(v95,"bosnia","norway","croatia","netherlands");
    eurovision+=Vote(v85,"ireland","greece","moldova","belarus");
    eurovision+=Vote(v60,"andora","lithiania","hungary","germany","estonia","france","italy","andora","luxembourg");
    eurovision+=Vote(v6,"ireland");
    eurovision+=Vote(v22,"belgium","kazakhastan","andora","slovakia","norway");
    eurovision+=Vote(v87,"hungary");
    eurovision+=Vote(v74,"spain","ukraine");
    eurovision+=Vote(v37,"luxembourg");
    eurovision+=Vote(v73,"austria");
    eurovision+=Vote(v66,"slovakia","bulgaria","turkey","france","russia","luxembourg","georgia","andora","netherlands");
    eurovision+=Vote(v58,"andora");
    eurovision+=Vote(v80,"armenia");
    eurovision+=Vote(v98,"sweden","ukraine");
    eurovision+=Vote(v85,"andora","bulgaria","italy","france","georgia","netherlands","slovakia","ireland","armenia");
    eurovision+=Vote(v30,"spain","spain");
    eurovision+=Vote(v88,"russia");
    eurovision+=Vote(v43,"turkey","italy","georgia","belgium","turkey","israel","norway","austria");
    eurovision+=Vote(v86,"georgia");
    eurovision+=Vote(v18,"armenia","slovenia","estonia","israel");
    eurovision+=Vote(v16,"turkey");
    eurovision+=Vote(v84,"greece","netherlands","malta","spain","lithiania");
    eurovision+=Vote(v61,"malta");
    eurovision+=Vote(v76,"france");
    eurovision+=Vote(v18,"norway","croatia","italy","kazakhastan","luxembourg","hungary");
    eurovision+=Vote(v4,"turkey");
    eurovision+=Vote(v47,"moldova","croatia","italy","andora","spain");
    eurovision+=Vote(v42,"netherlands");
    eurovision+=Vote(v92,"switzerland");
    eurovision+=Vote(v20,"greece");
    eurovision+=Vote(v31,"croatia","georgia");
    eurovision+=Vote(v22,"malta","switzerland","belarus","lithiania","serbia");
    eurovision+=Vote(v26,"italy");
    eurovision+=Vote(v44,"austria");
    eurovision+=Vote(v71,"slovakia");
    cout<<eurovision<<endl;



}