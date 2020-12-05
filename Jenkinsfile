pipeline {
  agent any
  stages {
    stage('Prepare Submodules') {
      steps {
        checkout([
          $class: 'GitSCM',
          branches: scm.branches,
          doGenerateSubmoduleConfigurations: true,
          extensions: scm.extensions + [[$class: 'SubmoduleOption', parentCredentials: true]],
          userRemoteConfigs: scm.userRemoteConfigs
        ])
      }
    }
    stage('Build') {
      parallel {
        stage('Build C15') {
          agent {
            label 'gcc-arm-none-eabi'
          }
          steps {
            sh '''make C15'''
            archiveArtifacts artifacts: 'build/annepro2-shine-C15.bin', followSymlinks: false
          }
        }

        stage('Build C18') {
          agent {
            label 'gcc-arm-none-eabi'
          }
          steps {
            sh '''make C18'''
            archiveArtifacts artifacts: 'build/annepro2-shine-C18.bin', followSymlinks: false
          }
        }
      }
    }
  }
}