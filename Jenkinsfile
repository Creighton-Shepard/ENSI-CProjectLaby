pipeline {
    agent any
    stages {
        stage('First') {
            steps {
                sh 'printenv'
                sh 'echo test >> test.txt'
            }
        }
        stage('Second'){
            steps {
                sh 'touch second_test.txt'
            }
        }
        stage('Final'){
            when {
                branch 'test/ci'
            }
            steps {
                sh 'echo "changement detecté" >> chg.txt'
                sh 'ls -l'
            }
        }
    }
}
