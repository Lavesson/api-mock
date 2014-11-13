'use strict';

// Declare app level module which depends on views, and components
var app = angular.module('ApiMock', ['ngRoute', 'ui.bootstrap']).
    config(['$routeProvider', function($routeProvider) {
        $routeProvider.when("/", {
            templateUrl: "templates/overview.html",
            controller: "DashboardController"
        }).when("/endpoints", {
            templateUrl: "templates/endpoints.html",
            controller: "DashboardController"
        });
    }])
    .controller("DashboardController", ["$scope", "$modal", function($scope, $modal) {
        $scope.open = function () {
            $modal.open({
                templateUrl: "templates/addroute.html"
                //backdrop: false,
            });
        };

        $scope.apiList = [
            {
                apiId: 1,
                endpoint: "/api/test1",
                desc: "First API",
                resources: [
                    { uri: "/user" },
                    { uri: "/user/{id}" },
                    { uri: "/user/{id}/friends" },
                    { uri: "/offers/{date}" }
                ]},
            {
                apiId: 2,
                endpoint: "/api/test2",
                desc: "Second API",
                resources: [
                    { uri: "/cats" },
                    { uri: "/dogs" },
                    { uri: "/dogs/{id}" },
                    { uri: "/cats/{id}" }
                ]},
            {
                apiId: 3,
                endpoint: "/api/test3",
                desc: "Third API",
                resources: [
                    { uri: "/customer" },
                    { uri: "/sales" },
                    { uri: "/customer/{id}" },
                    { uri: "/customer/{id}/orders" }
                ]
            }
        ];

        $scope.currentApi = $scope.apiList[0];
    }]);
