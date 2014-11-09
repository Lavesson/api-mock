'use strict';

describe('ApiMock module', function() {
    beforeEach(module('ApiMock'));

    describe('Unit: DashboardController', function() {
        var ctrl, scope;
        beforeEach(inject(function($controller, $rootScope) {
            scope = $rootScope.$new();
            ctrl = $controller('DashboardController', {
                $scope: scope
            });
        }));

        //it('should...', inject(function() {
        //}));
    });
});
