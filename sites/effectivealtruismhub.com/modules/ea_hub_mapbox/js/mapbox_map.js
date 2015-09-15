jQuery('document').ready( function () {
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
}
);
