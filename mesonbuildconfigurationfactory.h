#pragma once
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/buildinfo.h>
#include <projectexplorer/kit.h>
#include <projectexplorer/namedwidget.h>

namespace xxxMeson {

class MesonBuildInfo : public ProjectExplorer::BuildInfo {
public:
    MesonBuildInfo(const ProjectExplorer::IBuildConfigurationFactory *f) : ProjectExplorer::BuildInfo(f) { }

    QString mesonPath;

    bool operator==(const BuildInfo &o) const
    {
        if (!ProjectExplorer::BuildInfo::operator==(o))
            return false;

        auto other = static_cast<const MesonBuildInfo *>(&o);
        return mesonPath == other->mesonPath;
    }

};

class MesonBuildConfiguration : public ProjectExplorer::BuildConfiguration
{
    Q_OBJECT

public:
    explicit MesonBuildConfiguration(ProjectExplorer::Target *parent);

public:
    ProjectExplorer::NamedWidget *createConfigWidget() override;
    BuildType buildType() const override;

    QString mesonPath() const;
    void setMesonPath(const QString &mesonPath);

    bool fromMap(const QVariantMap &map) override;
    QVariantMap toMap() const override;

private:
    QString m_mesonPath;
};


class MesonBuildConfigurationFactory : public ProjectExplorer::IBuildConfigurationFactory
{
public:
    MesonBuildConfigurationFactory(QObject *parent = nullptr);

    // IBuildConfigurationFactory interface
public:
    int priority(const ProjectExplorer::Target *parent) const override;
    QList<ProjectExplorer::BuildInfo *> availableBuilds(const ProjectExplorer::Target *parent) const override;
    int priority(const ProjectExplorer::Kit *k, const QString &projectPath) const override;
    QList<ProjectExplorer::BuildInfo *> availableSetups(const ProjectExplorer::Kit *k, const QString &projectPath) const override;
    ProjectExplorer::BuildConfiguration *create(ProjectExplorer::Target *parent, const ProjectExplorer::BuildInfo *info) const override;
    bool canRestore(const ProjectExplorer::Target *parent, const QVariantMap &map) const override;
    ProjectExplorer::BuildConfiguration *restore(ProjectExplorer::Target *parent, const QVariantMap &map) override;
    bool canClone(const ProjectExplorer::Target *parent, ProjectExplorer::BuildConfiguration *product) const override;
    ProjectExplorer::BuildConfiguration *clone(ProjectExplorer::Target *parent, ProjectExplorer::BuildConfiguration *product) override;
    ProjectExplorer::BuildInfo *createBuildInfo(const ProjectExplorer::Kit *k, const QString &projectPath, ProjectExplorer::BuildConfiguration::BuildType type) const;

private:
    bool correctProject(const ProjectExplorer::Target *parent) const;

};

}
