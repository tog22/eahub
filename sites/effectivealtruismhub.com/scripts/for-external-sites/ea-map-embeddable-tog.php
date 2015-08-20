<!DOCTYPE html>
<html>
	<head>
		<title>Map of local effective altruism groups</title>
		<!-- Same version of jQuery as used on EA Hub, in case add jQuery: -->
		<!-- <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script> -->
		<link type="text/css" rel="stylesheet" href="http://cdn.leafletjs.com/leaflet-0.7.3/leaflet.css" media="all" />
<link type="text/css" rel="stylesheet" href="http://cdnjs.cloudflare.com/ajax/libs/leaflet.markercluster/0.4.0/MarkerCluster.Default.css" media="all" />
<link type="text/css" rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css" media="all" />
<link type="text/css" rel="stylesheet" href="http://cdnjs.cloudflare.com/ajax/libs/Leaflet.awesome-markers/2.0.0/leaflet.awesome-markers.css" media="all" />
		<style type="text/css">
			/*
			body {overflow: hidden; }
			#noscroll.wrap {height:100%; overflow:hidden;}
			*/
			body {margin: 0px;}
		</style>
		<base target="_parent" />
	</head>
	<body>
		<div id="noscroll">
<!--
          start pasted map block
-->

    <script src="http://cdn.leafletjs.com/leaflet-0.7.3/leaflet.js"></script>
    <script src="http://cdnjs.cloudflare.com/ajax/libs/leaflet.markercluster/0.4.0/leaflet.markercluster.js"></script>
        <script src="http://cdnjs.cloudflare.com/ajax/libs/Leaflet.awesome-markers/2.0.0/leaflet.awesome-markers.js"></script>
        
        
	<div id="map" style="
	position: relative;
	max-width: 1000px;
	width: 940px;
	height: 570px;
	"></div>
    <!-- 
    ==SMALL VERSION==
    <div id="map" style="
    position: relative;
    width: 480px;
    height: 280px
    "></div>

        ==LARGE VERSION==
	<div id="map" style="
	width: 100%;
	position: relative;
	margin: 4em auto;
	max-width: 1000px;
	width: 1000px;
	height: 570px;
	"></div>
     -->

    <script>
     //<![CDATA[
     window.groupsData = <?php include 'group-locations.json';?>;
     window.individualsData = <?php include 'individual-locations.json';?>;
     //]]>
    </script>

    <script>
     var EAIndividualsCluster = new L.MarkerClusterGroup({maxClusterRadius: 60})
         ,EAGroupCluster = new L.MarkerClusterGroup({maxClusterRadius: 60});


     var markerData = window.individualsData;
     for(var i = 0; i < markerData.length; i++) {
       var currentMarkerData = markerData[i];
       var latlng = currentMarkerData.latlng;
       var popup = currentMarkerData.popup;
       var marker = new L.marker(latlng).bindPopup(popup);
       EAIndividualsCluster.addLayer(marker);
     }
      
     var markerData = window.groupsData;
     for(var i = 0; i < markerData.length; i++) {
       var currentMarkerData = markerData[i];
       var latlng = currentMarkerData.latlng;
       var popup = currentMarkerData.popup;
       var marker = new L.marker(latlng, {icon: L.AwesomeMarkers.icon({icon: 'users', markerColor: 'orange', prefix: 'fa', iconColor: 'black'}) }).bindPopup(popup);
       EAGroupCluster.addLayer(marker);
     }

    var streets   = L.tileLayer('https://api.tiles.mapbox.com/v4/shared-ea-account.ee9fbb54/{z}/{x}/{y}.png?access_token=pk.eyJ1Ijoic2hhcmVkLWVhLWFjY291bnQiLCJhIjoiM2M3YjdmNzcwNDg1MmM5YjliMzIyNThkZTc2OWJjMWUifQ.-QAdcCLKxJZr8dtAofvdsw',{
       maxZoom: 18,
       attribution: 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, ' +
		            '<a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, ' +
		            'Imagery &copy <a href="http://mapbox.com">Mapbox</a>',
     })

     var map = L.map('map', {
       center: [25,7],
       zoom: 2,
       layers: [streets,EAGroupCluster]
     });

    var baseMaps = {
        "Individuals": EAIndividualsCluster,
        "Groups": EAGroupCluster
    };

    L.control.layers(baseMaps, null,{collapsed:false,position:"bottomleft"}).addTo(map);
    </script>

		</div>
	</body>
</html>
